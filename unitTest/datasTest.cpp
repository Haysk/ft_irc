#include "../src/include/utils.hpp"
#include "../src/model/Datas.h"
#include "../src/model/User.h"
#include "../src/model/Channel.h"

int main () {
	Datas *servDatas = NULL;

	servDatas = new Datas();
	servDatas->newUser("toto", "toto le boss", "127.0.0.1", 118218);
	try {
		servDatas->newUser("toto", "toto le boss", "127.0.0.1", 118218);
	} catch (exception &e) {
		cout << e.what() << endl;
	}
	try {
		cout << servDatas->getUser("tot") << endl;
	} catch (exception &e) {
		cout << e.what() << endl;
	}
	User &toto = servDatas->getUser("toto");
	cout << toto << endl;
	cout << "------------------------------------------" << endl;
	toto.createChannel(*servDatas, "totoChannel", 0);
	cout << toto << endl;
	try {
		toto.createChannel(*servDatas, "totoChannel", 0);
	} catch (exception &e) {
		cout << e.what() << endl;
	}
	cout << toto << endl;

	delete servDatas;
}
