#include"includes.h"
using namespace std;
dpp::cluster bot(BOT_TOKEN);

int main() {
    bot.on_log(dpp::utility::cout_logger());
 
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "echo") {
            dpp::snowflake channel = event.command.get_channel().id;
            if (bancheck(event.command.get_issuing_user().id)==true){
                std::string testovo = std::get<std::string>(event.get_parameter("text"));
                bot.message_create(dpp::message(channel, testovo));
                cout << "Команда сработала! " << testovo << " | " << event.command.get_issuing_user().global_name << " (" << event.command.get_issuing_user().username << ", " << event.command.get_issuing_user().id << ")" << endl;
                event.thinking(true);
                event.delete_original_response();
            }else {
                event.reply(dpp::message("[ ! ] Вы заблокированы за нарушения"));
            }
        }

        if (event.command.get_command_name() == "random"){
            double from = get<double>(event.get_parameter("от"));
            double to = get<double>(event.get_parameter("до"));
            long int cfrom = from;
            long int cto = to;
            switch (bancheck(event.command.get_issuing_user().id)){
                case true:
                    event.thinking();
                    if (from > 0 && to > 0 && from < to){
                    srand(time(NULL));
                    long int raznica = to +1 - from;
                    long int random = rand() % raznica ;
                    long int randomi = from + random;
                    event.edit_original_response("Вам выпало:" + to_string( randomi ));
                    } else{
                        event.edit_original_response(dpp::message("Число от должно быть < числа до и ни одно число не равно 0!"));
                    } break;
                
                case false:
                    event.reply(dpp::message("[ ! ] Вы заблокированы за нарушения"));
                    break;
            }
         }

         if (event.command.get_command_name()=="calculate"){
            event.thinking();
            dpp::snowflake channel = event.command.get_channel().id;
            string primer = get<string>(event.get_parameter("пример"));
            string term_cmd = "calc '" + primer + "' > r.txt && echo $? > status.txt";
            int sz =term_cmd.length();
            char* converted = new char[sz+1];
            strcpy(converted, term_cmd.c_str());
            system(converted);

            ifstream file("r.txt");
            string answer;
            getline(file, answer);
            
            switch(bancheck(event.command.get_issuing_user().id)){
                case true:
                    if (answer != "" && answer.length() <= 2000){
                        event.edit_original_response(answer);
                    }else{
                        if(answer.length()>2000){
                            dpp::message err2(channel, "[ ! ] Ответ слишком длинный (>2000 символов)");
                            bot.message_create(err2);
                        }else{
                            dpp::message err1(channel, "[ ! ] Пример содержит ошибку");
                            bot.message_create(err1);
                         }
                        event.delete_original_response();
                    }
                    
                    break;
                case false:
                    event.edit_original_response(dpp::message("[ ! ] Вы заблокированы за нарушения"));
                    break;
            }
         }

         if(event.command.get_command_name()=="info"){
            event.reply("> AbstractBot\nСоздатель: AbstractDevs\n\n> Простой бот, написанный на C++ с использованием библиотеки D++\n\n> GitHub: \n> https://github.com/AbstractDevs70/JustABot-cpp");
         }

         if(event.command.get_command_name()=="about"){
            dpp::snowflake usrid = get<dpp::snowflake>(event.get_parameter("пользователь"));
            dpp::user usr = event.command.get_resolved_user(usrid);
            dpp::message infor("> ## 🔰 Общедоступная информация\n> :globe_with_meridians: Глобальный ник: "+usr.global_name+"\n> :white_check_mark: Юзернейм: "+usr.username+"\n> :passport_control: Айди: "+to_string(usr.id)+"\n\n> []( "+usr.get_default_avatar_url()+")");

            string blocked;
            if(bancheck(usr.id)==true){
                blocked = "Нет";
            }else{
                 blocked = "Да";
            }

            dpp::embed emb = dpp::embed()
                .set_title("Информация о " + usr.username)
                .set_description("> :globe_with_meridians: Глобальный ник: "+usr.global_name+"\n> :white_check_mark: Юзернейм: "+usr.username+"\n> :passport_control: Айди: "+to_string(usr.id)+"\n> :no_entry_sign: Заблокирован: "+ blocked)
                .set_image(usr.get_avatar_url())
                .add_field(
                    "Пинг",
                    usr.get_mention(),
                    true
                );
                if( usr.is_bot() == true){
                    emb.set_color(dpp::colors::purple);
                    emb.add_field(
                        "Является",
                        "Ботом",
                        true
                    );
                }else{
                    emb.set_color(dpp::colors::mint);
                    emb.add_field(
                        "Является",
                        "Пользователем",
                        true
                    );
                }
            event.reply(emb);
         }

    });
 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand echo ("echo", "Выводит ваш текст в чат от имени бота", bot.me.id);
            echo.add_option(
                dpp::command_option(dpp::co_string, "text", "Текст", true)
            );

            dpp::slashcommand random ("random", "Попытай удачу", bot.me.id);
            random.add_option(
                dpp::command_option(dpp::co_number, "от", "От какого числа", true)
            );
            random.add_option(
                dpp::command_option(dpp::co_number, "до", "До какого числа", true)
            );

            dpp::slashcommand calc ("calculate", "Высчитать пример", bot.me.id);
            calc.add_option(
                dpp::command_option(dpp::co_string, "пример", "Ваш пример", true)
            );

            dpp::slashcommand info ("info", "Немного информации", bot.me.id);

            dpp::slashcommand about ("about", "Получить информацию об участнике", bot.me.id);
            about.add_option(
                dpp::command_option(dpp::co_user, "пользователь", "...", true)
            );

            
            bot.global_command_create(echo);
            bot.global_command_create(random);
            bot.global_command_create(calc);
            bot.global_command_create(info);
            bot.global_command_create(about);
            bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_custom, "У меня появился гитхаб (используй /info)"));
        }
    });
 
    bot.start(dpp::st_wait);
    return 0;
}
