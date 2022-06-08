#include "../../src/include/utils.hpp"
#include "../../src/model/Datas.hpp"
#include "../../src/model/User.hpp"
#include "../../src/model/Channel.hpp"

void datasTest(Datas &servDatas) {
	try {
		cout << "--------------------NEW USER--------------------" << endl;
		servDatas.newUser("toto", "xx-toto le boss-xx", "127.0.0.1", 118218);
		servDatas.newUser("tata", "tata la belle gosse", "127.0.0.1", 71212);
		User &toto = servDatas.getUser("toto");
		User &tata = servDatas.getUser("tata");
		cout << toto << endl;
		cout << tata << endl;

		try {
			servDatas.newUser("toto", "xx-toto le boss-xx", "127.0.0.1", 118218);
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}

		try {
			cout << servDatas.getUser("tot") << endl;
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}

		cout << "--------------------CREATE CHANNEL--------------------" << endl;
		toto.createChannel(servDatas, "totoChannel", 0);
		cout << toto << endl;
		toto.createChannel(servDatas, "totoChannel2", 0);
		cout << toto << endl;

		try {
			toto.createChannel(servDatas, "totoChannel", 0);
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}

		cout << "--------------------JOIN CHANNEL--------------------" << endl;
		tata.joinChannel(servDatas, "totoChannel");
		cout << tata << endl;
		cout << servDatas.getChannel("totoChannel") << endl;
		
		try {
			tata.joinChannel(servDatas, "totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}
		try {
			toto.joinChannel(servDatas, "totoChannel");
		} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
		}

		

	} catch (datasException &e) {
			cout << e.getOption() << " : " << e.what() << endl;
	}
}
