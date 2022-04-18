//놀이공원 요금 계산 
#include <stdio.h>
#include <time.h>

int main () {
	//변수
	int tk1, tk2, ticketnum, Special_Offer, Age, ticketCase, ticketPrice, totalTicketPrice, today, yyyymmdd, AgeType;
	int	idFront, idFrontMonth, idFrontDay, idBack, idBackFirst;
	int	next, again, counter=0;
	
	//권종 - 종합이용권 (SH'S--WORLD+민속박물관)	
	const int ADULT_DAY_ALL = 62000, TEEN_DAY_ALL = 54000, CHILD_DAY_ALL = 47000, BABY_DAY_ALL = 15000,
	    	  AFTER4_ADULT_ALL = 50000, AFTER4_TEEN_ALL = 43000, AFTER4_CHILD_ALL = 36000, AFTER4_BABY_ALL = 15000;
	    	  
	//권종 - 파크이용권 (SH'S--WORLD)  	  
	const int ADULT_DAY = 59000, TEEN_DAY = 52000, CHILD_DAY = 46000, BABY_DAY = 15000,
	    	  AFTER4_ADULT = 47000, AFTER4_TEEN = 41000, AFTER4_CHILD = 35000, AFTER4_BABY = 15000;
	    	  
	    	  
	const int OLDMAN_Age=65, TEEN_Age_MAX=18, TEEN_CHILD_Age=13, CHILD_BABY_Age=3, BABY_Age_MIN=1;

	time_t timer;
	struct tm* t;
	timer = time(NULL); 
	t = localtime(&timer);

	do { 
		int ticketCaseArr[10]={0}, Special_OfferArr[10]={0}, AgeTypeArr[10]={0}, ticketPriceArr[10]={0}, ticketnumArr[10]={0}, todayArr[10]={0};
		 
		FILE *filePointer = fopen("SH'S--WORLD.csv","a+");
		
		do {
			printf("================= SH'S -- WORLD =================\n") ;
			// 이용권 종류 (종합 or 파크)
			do {
				printf("\n이용권의 종류를 선택해주세요.\n");
				printf("1. 종합이용권 (SH'S--WORLD+민속박물관)\n2. 파크이용권 (SH'S--WORLD)\n");
				scanf("%d",&tk1);
			} while(tk1 >2) ;
			
			//주,야간권 선택
			do {
				printf("\n입장시간에 따른 이용권을 선택해 주세요.\n");
				printf("1. 1Day 2. After4\n");
				scanf("%d",&tk2);
			} while(tk2 >2) ;
			
			//주민번호
			do {
				printf("\n주민등록번호 13자리를 입력해주세요. ('-'대신 한칸 띄어주세요.)\n");
				scanf("%6d %7d",&idFront, &idBack);
				
				idBackFirst = idBack/1000000;
				idFrontMonth = (idFront/100)%100;
				idFrontDay = idFront%100;
			} while(idBackFirst >4 || idBackFirst<1 || idFrontDay>31 || idFrontDay<1 || idFrontMonth >12 ||
						idFrontDay <1 || idBack > 9999999 || idFront>999999 ||(idFrontMonth = 2 && idFrontDay>29)) ;	
			
			//우대사항
			do {	
				printf("\n우대사항을 선택해주세요.\n");
				printf("1.없음\n2.장애인\n3.국가유공자\n");
				printf("4.휴가장병\n5.임산부\n6.다자녀\n");
				scanf("%d",&Special_Offer);
			} while(Special_Offer>6) ;
	
			//구매수 
			do {
				printf("\n티켓 몇 장 구매하시겠습니까?.\n");
				scanf("%d",&ticketnum);
				
				if ( ticketnum>10 ){
					printf("(최대 10장 구매가능)\n\n");
				} 
			} while(ticketnum>10) ;
	
			
			today= (t->tm_year + 1900)*10000 + (t->tm_mon + 1)*100 + t->tm_mday;  
			
			//1900년생, 2000년생 
			if (idBackFirst ==3 || idBackFirst == 4) { 
				yyyymmdd = idFront + 20000000;
			} else {                  
				yyyymmdd = idFront + 19000000;
			} 
		
			//만 나이
			Age = (today - yyyymmdd)/10000;
			
			
			if (Age <CHILD_BABY_Age && Age >=BABY_Age_MIN) { 
				AgeType=4; 
			} else if ((Age >= CHILD_BABY_Age && Age <TEEN_CHILD_Age)) {
				AgeType = 3; 
			} else if (Age >= TEEN_CHILD_Age && Age <= TEEN_Age_MAX) {
				AgeType = 2; 
			} else if ( Age >= OLDMAN_Age ) {
				AgeType = 5;  
			} else {
				AgeType = 1; 
			}
			
			 
			if (tk1==1 && tk2==1) {
				ticketCase = 1; 
			} else if (tk1==1 && tk2==2) {
				ticketCase =2; 
			} else if (tk1 == 2 && tk2 == 1) {
				ticketCase = 3; 
			} else {
				ticketCase = 4;  
			} 
			
			//우대사항 적용 전
			if ( AgeType == 1) { 
				if (ticketCase== 1) {        
					ticketPrice= ADULT_DAY_ALL;
				} else if (ticketCase==2) {  
					ticketPrice= AFTER4_ADULT_ALL;
				}else if (ticketCase ==3) {  
					ticketPrice= ADULT_DAY;
				} else {                         
					ticketPrice= AFTER4_ADULT;
				}
			} else if ( AgeType == 2) {  
				if (ticketCase== 1) {
					ticketPrice=TEEN_DAY_ALL;
				} else if (ticketCase==2) {
					ticketPrice=AFTER4_TEEN_ALL;
				}else if (ticketCase ==3) {
					ticketPrice=TEEN_DAY;
				} else {
					ticketPrice=AFTER4_TEEN;
				}
			} else if ( AgeType == 3) { 
				if (ticketCase== 1) {
					ticketPrice=CHILD_DAY_ALL;
				} else if (ticketCase==2) {
					ticketPrice=AFTER4_CHILD_ALL;
				}else if (ticketCase ==3) {
					ticketPrice=CHILD_DAY;
				} else {
					ticketPrice=AFTER4_CHILD;
				}
			} else if (AgeType == 5) { 
				if (ticketCase== 1) {
					ticketPrice=CHILD_DAY_ALL;
				} else if (ticketCase==2) {
					ticketPrice=AFTER4_CHILD_ALL;
				}else if (ticketCase ==3) {
					ticketPrice=CHILD_DAY;
				} else {
					ticketPrice=AFTER4_CHILD;
				}
			} else {                  
				if (ticketCase== 1) {
					ticketPrice=BABY_DAY_ALL;
				} else if (ticketCase==2) {
					ticketPrice=AFTER4_BABY_ALL;
				}else if (ticketCase ==3) {
					ticketPrice=BABY_DAY;
				} else {
					ticketPrice=AFTER4_BABY;
				}
			}
			
			//우대사항 적용
			if (Special_Offer == 2) {
				ticketPrice = ticketPrice/2 ; 
			} else if (Special_Offer == 3) {
				ticketPrice = ticketPrice/2 ;
			} else if (Special_Offer == 4 && tk1==1) { 
				ticketPrice = (int)(ticketPrice*0.51);
			} else if (Special_Offer == 5 && tk1==1 ) {
				ticketPrice = ticketPrice/2;
			} else if (Special_Offer == 6 && tk1==1) {
				ticketPrice = (int)(ticketPrice*0.7);
			}
			//최종 가격
			ticketPrice *= ticketnum;
			
			//총액 출력
			if (ticketPrice==0){
				printf("\n무료 입장 입니다.\n");
			}
			else {
				printf ("\n%d매의  총금액은 %d원 입니다.\n",ticketnum,ticketPrice) ;
			}
			
			ticketCaseArr[counter] = ticketCase;
			Special_OfferArr[counter] = Special_Offer;
			AgeTypeArr[counter] = AgeType;
			ticketPriceArr[counter] = ticketPrice;
			ticketnumArr[counter]=ticketnum;
			totalTicketPrice += ticketPrice; 
			todayArr[counter]=today; 
			
			counter++;
			
			printf("\n계속 이용권을 구매하시겠습니까?\n1.YES\n2.NO\n");
			scanf("%d",&again); 
			
			//변수 초기화
			tk1=0, tk2=0, Special_Offer=0, ticketnum=0, idFront=0, idBack=0, AgeType=0, ticketPrice=0;  

		} while(again == 1);
		
		
		// 영수증 출력
		printf("\n\n==================================== %s ====================================\n","SH'S -- WORLD") ;
		printf("%s\t\t%s\t     %s\t  %s\t\t%s\n\n","선택사항","연  령","매수","가격","우대사항");
		for (int i =0; i<counter; i++) {
			//데이터 파일형식 저장 
			fprintf(filePointer,"%d,%d,%d,%d,%d,%d\n",
								todayArr[i],ticketCaseArr[i],Special_OfferArr[i],AgeTypeArr[i],ticketnumArr[i],ticketPriceArr[i]);
			switch (ticketCaseArr[i]) {
				case 1:
					printf("%s","종합이용권 - 1Day");
					break;
				case 2:
					printf("%s","종합이용권 - After4");
					break;
				case 3:
					printf("%s","파크이용권 - 1Day");
					break;
				case 4:
					printf("%s","파크이용권 - After4");
					break;
				default:
					break;
			}
			
			switch (AgeTypeArr[i]) {
				case 1:
					printf("\t%s","어  른");
					break;
				case 2:
					printf("\t%s","청소년");
					break;
				case 3:
					printf("\t%s","어린이");
					break;
				case 4:
					printf("\t%s","유  아");
					break;
				case 5:
					printf("\t%s","노  인");
					break;
				case 6:
					printf("\t%s","영  아");
					break;
				default:
					break;
			}
			
			printf("%10d%14d원\t",ticketnumArr[i],ticketPriceArr[i]) ;
			
			switch (Special_OfferArr[i]) {
				case 1:
					printf("%s\n","우대 없음.");
					break;
				case 2:
					printf("%s\n","장애인 할인");
					break;
				case 3:
					printf("%s\n","국가유공자 할인");
					break;
				case 4:
					printf("%s\n","휴가장병 할인");
					break;
				case 5:
					printf("%s\n","임산부 할인");
					break;
				case 6:
					printf("%s\n","다자녀 할인");
					break;
				default:
					break;
			}
		}
		printf("\nTOTAL PRICE :  %d원 입니다.", totalTicketPrice);
		printf("\n===================================================================================\n") ;
		printf("\n계속 주문하시겠습니까?\n1.YES\n2.NO\n");
		scanf("%d",&next);
		//변수 초기화 
		counter = 0;
		totalTicketPrice=0;
	} while(next == 1);
	return 0; 
} 
