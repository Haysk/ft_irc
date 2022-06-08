#include "../src/include/utils.hpp"
#include "../src/model/Datas.hpp"
#include "../src/model/User.hpp"
#include "../src/model/Channel.hpp"
#include "datas/datasTest.hpp"

int main () {
	Datas *servDatas;
	servDatas = new Datas();

	// DATAS USERTEST
	datasTest(*servDatas);

	delete servDatas;
}
