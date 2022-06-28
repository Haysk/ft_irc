#include "../../includes/utils.hpp"
#include "../../includes/Datas.hpp"
#include "../../includes/User.hpp"
#include "../../includes/Channel.hpp"

void datasTest(Datas &servDatas) {
	try {
		cout << "--------------------NEW USER--------------------" << endl;
		servDatas.newUser(1);
		servDatas.newUser(2);
		User &toto = servDatas.getUser(1);
		toto.setUserName("toto");
		toto.setNickName("toto nickname");
		User &tata = servDatas.getUser(2);
		tata.setUserName("tata");
		tata.setNickName("tata nickname");
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
		toto.createChannel("totoChannel", 0);
		cout << toto;
		toto.createChannel("totoChannel2", 0);
		cout << toto;
		try {
			toto.createChannel("totoChannel", 0);
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << "--------------------JOIN CHANNEL--------------------" << endl;
		tata.joinChannel("totoChannel");
		cout << tata;
		cout << servDatas.getChannel("totoChannel") << endl;
	cout << "totnroa";
		try {
			tata.joinChannel("totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		try {
			toto.joinChannel("totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << "--------------------QUIT CHANNEL--------------------" << endl;
		tata.quitChannel("totoChannel");
		cout << servDatas.getChannel("totoChannel") << endl;
		cout << tata;
		cout << toto;
		toto.quitChannel("totoChannel");
		cout << toto;
		try {
			cout << servDatas.getChannel("totoChannel") << endl;
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << tata;
		cout << toto;
		cout << "--------------------KICK CHANNEL--------------------" << endl;
		tata.joinChannel("totoChannel2");
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
		tata.joinChannel("totoChannel2");
		try {
			tata.mode("totoChannel2", MODE_I, 1);
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		tata.quitChannel("totoChannel2");
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
		tata.joinChannel("totoChannel2");
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
			tata.joinChannel("totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		cout << "--------------------CHANNEL INVITE--------------------" << endl;
		toto.createChannel("inviteChannel", MODE_I);
		cout << toto;
		try {
			tata.joinChannel("inviteChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		toto.invite("tata", "inviteChannel");
		tata.joinChannel("inviteChannel");
		cout << toto;
		cout << tata;
		cout << "--------------------CMD NAME--------------------" << endl;
		string tmp[] = {"inviteChanne", "totoChannel"};
		vector<string> chanList(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));
		toto.name(chanList);
		cout << endl;
		tata.quitChannel("totoChannel");
		toto.name(chanList);
		cout << endl;
		toto.name();
		cout << endl;
		tata.quitChannel("inviteChannel");
		toto.name();
		toto.quitChannel("inviteChannel");
		toto.quitChannel("totoChannel");
		cout << endl;
		toto.name();


	} catch (datasException &e) {
			cout << "fail " << e.getOption() << " : " << e.what() << endl;
	}
}
