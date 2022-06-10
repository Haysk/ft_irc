#include "../src/include/utils.hpp"
#include "../src/model/Datas.hpp"
#include "../src/model/User.hpp"
#include "../src/model/Channel.hpp"
#include "unitTest.hpp"

int main () {
	Datas *servDatas;
	servDatas = new Datas();

	// DATAS USERTEST
	datasTest(*servDatas);
	
	// PARSING UNITTEST
	parsingTest(*servDatas);

	delete servDatas;
}
