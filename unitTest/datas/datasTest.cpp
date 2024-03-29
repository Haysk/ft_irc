#include "../../includes/utils.hpp"
#include "../../includes/Datas.hpp"
#include "../../includes/User.hpp"
#include "../../includes/Channel.hpp"

User &createUser(Datas &servDatas, int fd, const string &userName, const string &nickName)
{
	string	nick = "NICK " + nickName;
	string	user = "USER " + userName;
	servDatas.newUser(fd);
	User &usr = servDatas.getUser(fd);
	usr.initUserName(user);
	usr.initNickName(servDatas.getUsers(), nick);
	return usr;	
}

void datasTest(Datas &servDatas) {
	try {
		cout << "--------------------NEW USER--------------------" << endl;
		User &toto = createUser(servDatas, 1, "toto", "toto_nick");
		User &tata = createUser(servDatas, 2, "tata", "tata_nick");
		cout << toto;
		cout << tata;
		try {
			servDatas.newUser(1);
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		try {
			cout << servDatas.getUser("tot") << endl;
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << "--------------------CREATE CHANNEL--------------------" << endl;
		toto.join("totoChannel");
		cout << toto;
		toto.join("totoChannel2");
		cout << toto;
		try {
			toto.join("totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << servDatas.getChannel("totoChannel").getUser("toto").getNickName() << endl;
		cout << "--------------------JOIN CHANNEL--------------------" << endl;
		tata.join("totoChannel");
		cout << tata;
		cout << servDatas.getChannel("totoChannel") << endl;
		try {
			tata.join("totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		try {
			toto.join("totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << "--------------------QUIT CHANNEL--------------------" << endl;
		tata.part("totoChannel");
		cout << servDatas.getChannel("totoChannel") << endl;
		cout << tata;
		cout << toto;
		toto.part("totoChannel");
		cout << toto;
		try {
			cout << servDatas.getChannel("totoChannel") << endl;
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << tata;
		cout << toto;
		cout << "--------------------KICK CHANNEL--------------------" << endl;
		tata.join("totoChannel2");
		cout << tata;
		cout << toto;
		cout << servDatas.getChannel("totoChannel2") << endl;
		try {
			tata.kick("toto", "totoChannel2");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		toto.kick("tata", "totoChannel2");
		cout << tata << endl;
		cout << toto << endl;
		cout << servDatas.getChannel("totoChannel2") << endl;
		cout << "--------------------CHANNEL MODE--------------------" << endl;
		unsigned int t_mode = MODE_T;
		unsigned int it_mode = MODE_I | MODE_T;
		Channel &chan = servDatas.getChannel("totoChannel2");
		toto.mode("totoChannel2", MODE_I, 1);
		cout << "t mode : " << t_mode << endl;
		cout << "it mode : " << it_mode << endl;
		cout << "i mode : " << chan.getMode() << endl;
		cout << "i is i = " << chan.chanModeIs(MODE_I) << endl;
		cout << "i is t = " << chan.chanModeIs(MODE_T) << endl;
		cout << "i is it = " << chan.chanModeIs(MODE_I | MODE_T) << endl;
		toto.mode("totoChannel2", MODE_I, 0);
		toto.mode("totoChannel2", MODE_T, 1);
		cout << "t mode : " << chan.getMode() << endl;
		cout << "t is i = " << chan.chanModeIs(MODE_I) << endl;
		cout << "t is t = " << chan.chanModeIs(MODE_T) << endl;
		cout << "t is it = " << chan.chanModeIs(MODE_I | MODE_T) << endl;
		toto.mode("totoChannel2", MODE_T, 0);
		toto.mode("totoChannel2", MODE_I | MODE_T, 1);
		cout << "it mode : " << chan.getMode() << endl;
		cout << "it is i = " << chan.chanModeIs(MODE_I) << endl;
		cout << "it is t = " << chan.chanModeIs(MODE_T) << endl;
		cout << "it is it = " << chan.chanModeIs(MODE_I | MODE_T) << endl;
		toto.mode("totoChannel2", MODE_I | MODE_T, 0);
		try {
			tata.mode("totoChannel2", MODE_I, 1);
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		tata.join("totoChannel2");
		try {
			tata.mode("totoChannel2", MODE_I, 1);
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		tata.part("totoChannel2");
		cout << "mode : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I, 1);
		cout << "mode + i : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I, 1);
		cout << "mode + i : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_T, 1);
		cout << "mode + t : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_T, 1);
		cout << "mode + t : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I, 0);
		cout << "mode - i : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_T, 1);
		cout << "mode - i : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_T, 1);
		cout << "mode + t : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_T, 0);
		cout << "mode - t : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_T, 0);
		cout << "mode - t : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I, 1);
		cout << "mode + i : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I | MODE_T, 1);
		cout << "mode + it : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I | MODE_T, 1);
		cout << "mode + it : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I | MODE_T, 0);
		cout << "mode - it : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		toto.mode("totoChannel2", MODE_I | MODE_T, 0);
		cout << "mode - it : " << servDatas.getChannel("totoChannel2").getMode() << endl;
		cout << "--------------------CHANNEL TOPIC--------------------" << endl;
		try {
			toto.topic("totoChannel2", "totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		try {
			toto.topic("totoChannel1", "totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		try {
			tata.topic("totoChannel2", "totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		tata.join("totoChannel2");
		try {
			tata.topic("totoChannel2", "totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		toto.mode("totoChannel2", MODE_T, 1);
		toto.topic("totoChannel2", "totoChannel");
		cout << toto;
		cout << tata;
		try {
			tata.join("totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << "--------------------CHANNEL INVITE--------------------" << endl;
		toto.join("inviteChannel");
		toto.mode("inviteChannel", MODE_I, 1);
		cout << toto;
		try {
			tata.join("inviteChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		toto.invite("tata", "inviteChannel");
		tata.join("inviteChannel");
		cout << toto;
		cout << tata;
		cout << "--------------------CMD NAME--------------------" << endl;
		string tmp[] = {"inviteChanne", "totoChannel"};
		vector<string> chanList(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));
		toto.names(chanList);
		cout << endl;
		tata.part("totoChannel");
		toto.names();
		cout << "-----------------" << endl;
		tata.join("totoChannel");
		toto.names();
		cout << endl;
		tata.join("inviteChannel");
		toto.names();
		cout << endl;
		toto.join("totoChannel");
		toto.names();
		cout << endl;
		toto.join("inviteChannel");
		toto.names();
		cout << endl;
//		toto.part("inviteChannel");
//		toto.part("totoChannel");
//		cout << endl;
//		toto.names();
//

	} catch (datasException &e) {
			cout << "fail " << e.getOption() << " : " << e.what() << endl;
	}
}
