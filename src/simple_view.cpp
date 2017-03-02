#include <stdio.h>
#include <homerus/annri.hpp>
int main(int argc,char* argv[])
{
using namespace folklore::homerus;
using namespace std;
using ana::get_v;
	if(argc==1)
	{
		printf("usage : %s [filename]\n",argv[0]);
		return 0;
	}
	homerus<ana::annri> hom(argv[1]);
	if(hom)
	for(auto data:hom)
	{
		auto energy = get_v<ana::energy >(data);
		auto tof    = get_v<ana::time   >(data);
		auto ch     = get_v<ana::channel>(data); 
		printf("energy = %u\n",energy);
		printf("tof    = %u\n",tof   );
		printf("ch     = %u\n",ch    );
	}
	return 0;
}

