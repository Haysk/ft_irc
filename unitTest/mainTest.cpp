#include "../includes/utils.hpp"
#include "../includes/Datas.hpp"
#include "../includes/User.hpp"
#include "../includes/Channel.hpp"
#include "datas/datasTest.hpp"

int main () {
	Datas *servDatas;
	servDatas = new Datas();

	// DATAS USERTEST	
	datasTest(*servDatas);

	delete servDatas;
}
