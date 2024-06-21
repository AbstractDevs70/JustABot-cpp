#include"includes.h"
using namespace std;
dpp::cluster bot(BOT_TOKEN);

int main() {
    bot.on_log(dpp::utility::cout_logger());
    cout << dpp::colors::green;
 
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "echo") {
            dpp::snowflake channel = event.command.get_channel().id;
            cout << "echo | ";
            if (bancheck(event.command.get_issuing_user().id)==true){
                std::string testovo = std::get<std::string>(event.get_parameter("text"));
                bot.message_create(dpp::message(channel, testovo));
                event.thinking(true);
                event.delete_original_response();
                cout << testovo;
            }else {
                event.reply(dpp::message("[ ! ] Вы заблокированы за нарушения"));
            }
            cout << " | " << event.command.get_issuing_user().username << endl; 
        }

        if (event.command.get_command_name() == "random"){
            double from = get<double>(event.get_parameter("от"));
            double to = get<double>(event.get_parameter("до"));
            long int cfrom = from;
            long int cto = to;
            cout << "random | ";
            switch (bancheck(event.command.get_issuing_user().id)){
                case true:
                    event.thinking();
                    if (from > 0 && to > 0 && from < to){
                    srand(time(NULL));
                    long int raznica = to +1 - from;
                    long int random = rand() % raznica ;
                    long int randomi = from + random;
                    event.edit_original_response("Вам выпало:" + to_string( randomi ));
                    cout << to_string(from) << "/" << to_string(to);
                    } else{
                        event.edit_original_response(dpp::message("Число от должно быть < числа до и ни одно число не равно 0!"));
                        cout << "Заблокировано";
                    } break;
                
                case false:
                    event.reply(dpp::message("[ ! ] Вы заблокированы за нарушения"));
                    cout << "Заблокировано";
                    break;
            }
            cout << " | " << event.command.get_issuing_user().username << endl; 
         }

         if (event.command.get_command_name()=="calculate"){
            cout << "calculate | ";
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
                        event.edit_original_response(primer + "=" + answer);
                        cout << primer;
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
                    cout << "Заблокировано";
                    break;
            }
            cout << " | " << event.command.get_issuing_user().username << endl; 
         }

         if(event.command.get_command_name()=="info"){
            event.reply("> AbstractBot\nСоздатель: AbstractDevs\n\n> Простой бот, написанный на C++ с использованием библиотеки D++\n\n> GitHub: \n> https://github.com/AbstractDevs70/JustABot-cpp");
            cout << "info | | " << event.command.get_issuing_user().username; 
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
            cout << "about | "<< usr.username << " | " << event.command.get_issuing_user().username << endl; 
         }

         if (event.command.get_command_name()=="embed"){
            cout << "embed | ";
            event.thinking(true);
            dpp::snowflake channel = event.command.get_channel().id;
            dpp::embed cemb = dpp::embed();
            if (event.get_parameter("цвет").index() != 0){
                uint32_t gget = get<long int>(event.get_parameter("цвет"));
                cemb.set_color(gget);
                cout << to_string(gget) << ", ";
            }
            if (event.get_parameter("заголовок").index() != 0){
                string gget = get<string>(event.get_parameter("заголовок"));
                cemb.set_title(gget);
                cout << gget << ", ";
            }
            if (event.get_parameter("описание").index() != 0){
                string gget = get<string>(event.get_parameter("описание"));
                cemb.set_description(gget);
                cout << gget << ", ";
            }
            if (event.get_parameter("изображение").index() != 0){
                string gget = get<string>(event.get_parameter("изображение"));
                cemb.set_image(gget);
                cout << gget << ", ";
            }
            if (event.get_parameter("картинка").index() != 0){
                string gget = get<string>(event.get_parameter("картинка"));
                cemb.set_thumbnail(gget);
                cout << gget << ", ";
            }
            if (event.get_parameter("ссылка").index() != 0){
                string gget = get<string>(event.get_parameter("ссылка"));
                cemb.set_url(gget);
                cout << gget << ", ";
            }
            if (event.get_parameter("футер-текст").index() != 0 && event.get_parameter("футер-иконка").index() != 0 ){
                string gget1 = get<string>(event.get_parameter("футер-текст"));
                string gget2 = get<string>(event.get_parameter("футер-иконка"));
                cemb.set_footer(
                    dpp::embed_footer()
                    .set_text(gget1)
                    .set_icon(gget2)
                );
                cout << gget1 << ", " << gget2 << ", ";
            }
            if (event.get_parameter("филд-заголовок").index() != 0 && event.get_parameter("филд-описание").index() != 0 && event.get_parameter("филд-инлайн").index() != 0){
                string gget1 = get<string>(event.get_parameter("филд-заголовок"));
                string gget2 = get<string>(event.get_parameter("филд-описание"));
                bool gget3 = get<bool>(event.get_parameter("филд-инлайн"));
                cemb.add_field(
                    gget1,
                    gget2,
                    gget3
                );
                cout << gget1 << ", " << gget2 << ", ";
            }

            if (event.get_parameter("филд2-заголовок").index() != 0 && event.get_parameter("филд2-описание").index() != 0 && event.get_parameter("филд2-инлайн").index() != 0){
                string gget1 = get<string>(event.get_parameter("филд2-заголовок"));
                string gget2 = get<string>(event.get_parameter("филд2-описание"));
                bool gget3 = get<bool>(event.get_parameter("филд2-инлайн"));
                cemb.add_field(
                    gget1,
                    gget2,
                    gget3
                );
                cout << gget1 << ", " << gget2 << ", ";
            }

            if (event.get_parameter("филд3-заголовок").index() != 0 && event.get_parameter("филд3-описание").index() != 0 && event.get_parameter("филд3-инлайн").index() != 0){
                string gget1 = get<string>(event.get_parameter("филд3-заголовок"));
                string gget2 = get<string>(event.get_parameter("филд3-описание"));
                bool gget3 = get<bool>(event.get_parameter("филд3-инлайн"));
                cemb.add_field(
                    gget1,
                    gget2,
                    gget3
                );
                cout << gget1 << ", " << gget2 << ", ";
            }

            if (event.get_parameter("филд4-заголовок").index() != 0 && event.get_parameter("филд4-описание").index() != 0 && event.get_parameter("филд4-инлайн").index() != 0){
                string gget1 = get<string>(event.get_parameter("филд4-заголовок"));
                string gget2 = get<string>(event.get_parameter("филд4-описание"));
                bool gget3 = get<bool>(event.get_parameter("филд4-инлайн"));
                cemb.add_field(
                    gget1,
                    gget2,
                    gget3
                );
                cout << gget1 << ", " << gget2 << ", ";
            }

            if (event.get_parameter("филд5-заголовок").index() != 0 && event.get_parameter("филд5-описание").index() != 0 && event.get_parameter("филд5-инлайн").index() != 0){
                string gget1 = get<string>(event.get_parameter("филд5-заголовок"));
                string gget2 = get<string>(event.get_parameter("филд5-описание"));
                bool gget3 = get<bool>(event.get_parameter("филд5-инлайн"));
                cemb.add_field(
                    gget1,
                    gget2,
                    gget3
                );
                cout << gget1 << ", " << gget2  << ", ";
            }

            dpp::message msg(channel, cemb);
            bot.message_create(msg);

            event.delete_original_response();
            cout << " | " << event.command.get_issuing_user().username << endl; 
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

            dpp::slashcommand embed ("embed", "Создать эмбед", bot.me.id);
            embed.add_option(
                dpp::command_option(dpp::co_integer, "цвет", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "заголовок", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "описание", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "изображение", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "картинка", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "ссылка", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд-заголовок", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд-описание", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_boolean, "филд-инлайн", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд2-заголовок", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд2-описание", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_boolean, "филд2-инлайн", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд3-заголовок", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд3-описание", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_boolean, "филд3-инлайн", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд4-заголовок", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд4-описание", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_boolean, "филд4-инлайн", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд5-заголовок", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "филд5-описание", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_boolean, "филд5-инлайн", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "футер-текст", "...", false)
            );
            embed.add_option(
                dpp::command_option(dpp::co_string, "футер-иконка", "...", false)
            );
            

            
            bot.global_command_create(echo);
            bot.global_command_create(random);
            bot.global_command_create(calc);
            bot.global_command_create(info);
            bot.global_command_create(about);
            bot.global_command_create(embed);
            bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_custom, "У меня появился гитхаб (используй /info)"));
        }
    });
 
    bot.start(dpp::st_wait);
    return 0;
}
