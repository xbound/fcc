#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define VIP 1
#define SVIP 2
#define TNED 4
//#define LOGFILE "logined"
char input[4096];
int main(int argc,char **argv){
	FILE *ini;
	unsigned long a,flag,vipst;//account
	time_t curt,endt;
	int r,ok,help,helpi;
	help=0;
	for(r=1;r<argc;++r){
		if(strcmp(argv[r],"-vip")==0||strcmp(argv[r],"--vip")==0){
		fprintf(stderr,"普通会员（VIP）权益：\n1.使用一级优化。\n2.生成动态链接库\n3.指定输出文件名\n4.支持的参数个数提升至10\n\n白金会员（SVIP）权益：\n1.使用二级优化和三级优化\n2.查看汇编代码\n3.不限参数个数\n\n");
		return 0;			
		}else if(strcmp(argv[r],"--help")==0||strcmp(argv[r],"-help")==0){
			help=1;
			helpi=r;
		}
	}
	curt=time(NULL);
	ok=0;
	ini=fopen(LOGFILE,"r");
	if(ini==NULL){
wl:
		fprintf(stderr,"请先登录太初编译器\n账号：");
		r=fscanf(stdin,"%lu",&a);
		if(r<1){
			fprintf(stderr,"输入的账号无效，请重新登录\n");
			return -1;
		}
		fprintf(stderr,"密码：");
		scanf("%s",input);
		ini=fopen(LOGFILE,"w");
		flag=0;
		vipst=0;
		fprintf(stderr,"正在登录中，请稍等");
		sleep(1);
		fprintf(stderr,"\n登录成功\n");
		fprintf(stderr,"\n太初编译器是一款由太初团队自主研发的，国产可控的高性能C语言编译器，以解决国外对核心技术的封锁为使命，以推动数字创新为导向，顺应软件国产化替代浪潮。\n太初编译器功能完全兼容clang和gcc，可作为gcc和clang的国产完全替代品。\n");
		fprintf(stderr,"\n首次使用请先阅读本协议：\n");
		fprintf(stderr,
		"本协议是您（个人或单一机构团体，以下简称用户）与太初团队公司（以下简称我司）之间关于本产品的协议，如果您不同意本协议，您不能使用本软件。\n\
\n\
一、本软件可以免费使用，但是不得反向工程，反向加密，反汇编，私自修改本软件及附属文件的任何部分。\n\
\n\
二、我司保留在任何时候为用户提供软件的升级版本并为此收费的权利。\n\
\n\
三、未明确的其他一切权利归我司所有。\n\
\n\
四、因使用本软件造成的一切后果，由用户自行承担。\n\
\n\
五、如果您未能遵守本协议中的条款，我司有权终止对用户的授权。终止授权时，您必须销毁所有该软件的复制品。\n\
\n\
\n"
				);
		fprintf(stderr,"（输入y同意本协议，n拒绝）：");
		fscanf(stdin,"%s",input);
		if((*input|32)!='y')return -1;

		if(ini!=NULL){
		fprintf(ini,"%lu %lu %lu",a,flag,vipst);
		fclose(ini);
		}else{
		fprintf(stderr,"登录失败\n");
		return -1;
		}
		fprintf(stderr,"使用%s 参数... 进行编译，使用参数--vip查看会员详情，--help获取帮助\n",argv[0]);
	}else{

		memset(input,0,sizeof(input));
		r=fread(input,1,4096,ini);
		fclose(ini);
		if(r>100&&0){
			fprintf(stderr,"账号信息过长，请重新登录\n");
			goto wl;
		}
		r=sscanf(input,"%lu %lu %lu",&a,&flag,&vipst);
		if(r<3){
			goto wl;
		}
		fprintf(stderr,"欢迎用户%lu，您当前为",a);
		if((curt-vipst)/86400>=30)
		{
			flag&=~VIP;
			flag&=~SVIP;
		}
		if(flag&VIP){
			if(flag&SVIP){
		fprintf(stderr,"白金会员S");
			}
		endt=vipst+30*86400;
		fprintf(stderr,"VIP 到期时间%s\n",ctime(&endt));
		}else{
		fprintf(stderr,"普通用户\n\n");
		}
		fprintf(stderr,"使用太初编译器造成的一切后果由用户自行承担，我司保留太初编译器所有解释权。\n严禁使用太初编译器进行违法犯罪活动！\n\n");
		if(argc>1)goto logs;
		fprintf(stderr,"使用%s 参数... 进行编译，使用参数--vip查看会员详情，--help获取帮助\n",argv[0]);
	}
return 0;
logs:
		if((flag&TNED)==0&&!help){
		fprintf(stderr,"检测到您未进行实名认证，进行实名认证后方可进行编译\n请输入您的真实姓名：");
		fscanf(stdin,"%s",input);
		fprintf(stderr,"身份证号：");
		fscanf(stdin,"%s",input);
		fprintf(stderr,"正在核实中，请稍等");
		sleep(1);
		fprintf(stderr,"\n验证成功\n");
		flag|=TNED;	
		}
	if(argc>11&&(flag&SVIP)==0){
		fprintf(stderr,"当前有%d个参数，非SVIP用户最多支持10个参数\n",argc-1);
asksvip:	fprintf(stderr,"是否充值SVIP？（60/月，输入y充值，n放弃）：");
		fscanf(stdin,"%s",input);
		if((*input|32)=='y'){
			fprintf(stderr,"处理中");
			sleep(1);
			fprintf(stderr,"\n充值成功\n");
			flag|=(SVIP|VIP);
			vipst=time(NULL);
		}else goto end;
	}
	if(argc>4&&(flag&VIP)==0){
		fprintf(stderr,"当前有%d个参数，非VIP用户最多支持3个参数\n",argc-1);
askvip:
		fprintf(stderr,"是否充值VIP？（30/月，输入y充值，n放弃）：");
		fscanf(stdin,"%s",input);
		if((*input|32)=='y'){
			fprintf(stderr,"处理中");
			sleep(1);
			fprintf(stderr,"\n充值成功\n");
			flag|=(VIP);
			vipst=time(NULL);
		}else goto end;
	}
	ok=1;
	for(r=1;r<argc;++r){
		if(strcmp(argv[r],"-O1")==0){
			if((flag&VIP)==0){
				fprintf(stderr,"检测到您使用了一级优化选项，此功能为VIP功能\n");
				ok=0;
				goto askvip;
			}
		}else if(strcmp(argv[r],"-shared")==0){
			if((flag&VIP)==0){
				fprintf(stderr,"检测到您引用了自定义动态链接库，此功能为VIP功能\n");
				ok=0;
				goto askvip;
			}
		}else if(strcmp(argv[r],"-o")==0){
			if((flag&VIP)==0){
				fprintf(stderr,"成为VIP后可自定义输出文件名（普通用户只能生成a.out）\n");
				ok=0;
				goto askvip;
			}
		}else if(strcmp(argv[r],"-O2")==0){
			if((flag&SVIP)==0){
				fprintf(stderr,"检测到您使用了二级优化选项，此功能为SVIP功能\n");
				ok=0;
				goto asksvip;
			}
		}else if(strcmp(argv[r],"-O3")==0){
			if((flag&SVIP)==0){
				fprintf(stderr,"检测到您使用了三级优化选项，此功能为SVIP功能\n");
				ok=0;
				goto asksvip;
			}
		}else if(strcmp(argv[r],"-S")==0){
			if((flag&SVIP)==0){
				fprintf(stderr,"成为SVIP后可查看汇编代码\n");
				ok=0;
				goto asksvip;
			}
		}
	}
end:	
	//saveaccount
	ini=fopen(LOGFILE,"w");
	if(ini!=NULL){
	fprintf(ini,"%lu %lu %lu",a,flag,vipst);
	fclose(ini);
	}
	if(ok){
		argv[0]="太初编译器";
		if(help){
			sprintf(input,"gcc %s |sed 's/[gG][cC][cC]/太初编译器/g' |sed 's/[cC][lL][aA][nN][gG]/太初编译器/g'",argv[helpi]);
			execlp("sh",argv[0],"-c",input,NULL);
		}else execvp("gcc",argv);
		if(help){
			sprintf(input,"clang %s |sed 's/[gG][cC][cC]/太初编译器/g' |sed 's/[cC][lL][aA][nN][gG]/太初编译器/g'",argv[helpi]);
			execlp("sh",argv[0],"-c",input,NULL);
		}else execvp("clang",argv);
		
	}
return -1;
}
