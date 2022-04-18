//���̰��� ��� ��� 
#include <stdio.h>
#include <time.h>

int main () {
	//����
	int tk1, tk2, ticketnum, Special_Offer, Age, ticketCase, ticketPrice, totalTicketPrice, today, yyyymmdd, AgeType;
	int	idFront, idFrontMonth, idFrontDay, idBack, idBackFirst;
	int	next, again, counter=0;
	
	//���� - �����̿�� (SH'S--WORLD+�μӹڹ���)	
	const int ADULT_DAY_ALL = 62000, TEEN_DAY_ALL = 54000, CHILD_DAY_ALL = 47000, BABY_DAY_ALL = 15000,
	    	  AFTER4_ADULT_ALL = 50000, AFTER4_TEEN_ALL = 43000, AFTER4_CHILD_ALL = 36000, AFTER4_BABY_ALL = 15000;
	    	  
	//���� - ��ũ�̿�� (SH'S--WORLD)  	  
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
			// �̿�� ���� (���� or ��ũ)
			do {
				printf("\n�̿���� ������ �������ּ���.\n");
				printf("1. �����̿�� (SH'S--WORLD+�μӹڹ���)\n2. ��ũ�̿�� (SH'S--WORLD)\n");
				scanf("%d",&tk1);
			} while(tk1 >2) ;
			
			//��,�߰��� ����
			do {
				printf("\n����ð��� ���� �̿���� ������ �ּ���.\n");
				printf("1. 1Day 2. After4\n");
				scanf("%d",&tk2);
			} while(tk2 >2) ;
			
			//�ֹι�ȣ
			do {
				printf("\n�ֹε�Ϲ�ȣ 13�ڸ��� �Է����ּ���. ('-'��� ��ĭ ����ּ���.)\n");
				scanf("%6d %7d",&idFront, &idBack);
				
				idBackFirst = idBack/1000000;
				idFrontMonth = (idFront/100)%100;
				idFrontDay = idFront%100;
			} while(idBackFirst >4 || idBackFirst<1 || idFrontDay>31 || idFrontDay<1 || idFrontMonth >12 ||
						idFrontDay <1 || idBack > 9999999 || idFront>999999 ||(idFrontMonth = 2 && idFrontDay>29)) ;	
			
			//������
			do {	
				printf("\n�������� �������ּ���.\n");
				printf("1.����\n2.�����\n3.����������\n");
				printf("4.�ް��庴\n5.�ӻ��\n6.���ڳ�\n");
				scanf("%d",&Special_Offer);
			} while(Special_Offer>6) ;
	
			//���ż� 
			do {
				printf("\nƼ�� �� �� �����Ͻðڽ��ϱ�?.\n");
				scanf("%d",&ticketnum);
				
				if ( ticketnum>10 ){
					printf("(�ִ� 10�� ���Ű���)\n\n");
				} 
			} while(ticketnum>10) ;
	
			
			today= (t->tm_year + 1900)*10000 + (t->tm_mon + 1)*100 + t->tm_mday;  
			
			//1900���, 2000��� 
			if (idBackFirst ==3 || idBackFirst == 4) { 
				yyyymmdd = idFront + 20000000;
			} else {                  
				yyyymmdd = idFront + 19000000;
			} 
		
			//�� ����
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
			
			//������ ���� ��
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
			
			//������ ����
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
			//���� ����
			ticketPrice *= ticketnum;
			
			//�Ѿ� ���
			if (ticketPrice==0){
				printf("\n���� ���� �Դϴ�.\n");
			}
			else {
				printf ("\n%d����  �ѱݾ��� %d�� �Դϴ�.\n",ticketnum,ticketPrice) ;
			}
			
			ticketCaseArr[counter] = ticketCase;
			Special_OfferArr[counter] = Special_Offer;
			AgeTypeArr[counter] = AgeType;
			ticketPriceArr[counter] = ticketPrice;
			ticketnumArr[counter]=ticketnum;
			totalTicketPrice += ticketPrice; 
			todayArr[counter]=today; 
			
			counter++;
			
			printf("\n��� �̿���� �����Ͻðڽ��ϱ�?\n1.YES\n2.NO\n");
			scanf("%d",&again); 
			
			//���� �ʱ�ȭ
			tk1=0, tk2=0, Special_Offer=0, ticketnum=0, idFront=0, idBack=0, AgeType=0, ticketPrice=0;  

		} while(again == 1);
		
		
		// ������ ���
		printf("\n\n==================================== %s ====================================\n","SH'S -- WORLD") ;
		printf("%s\t\t%s\t     %s\t  %s\t\t%s\n\n","���û���","��  ��","�ż�","����","������");
		for (int i =0; i<counter; i++) {
			//������ �������� ���� 
			fprintf(filePointer,"%d,%d,%d,%d,%d,%d\n",
								todayArr[i],ticketCaseArr[i],Special_OfferArr[i],AgeTypeArr[i],ticketnumArr[i],ticketPriceArr[i]);
			switch (ticketCaseArr[i]) {
				case 1:
					printf("%s","�����̿�� - 1Day");
					break;
				case 2:
					printf("%s","�����̿�� - After4");
					break;
				case 3:
					printf("%s","��ũ�̿�� - 1Day");
					break;
				case 4:
					printf("%s","��ũ�̿�� - After4");
					break;
				default:
					break;
			}
			
			switch (AgeTypeArr[i]) {
				case 1:
					printf("\t%s","��  ��");
					break;
				case 2:
					printf("\t%s","û�ҳ�");
					break;
				case 3:
					printf("\t%s","���");
					break;
				case 4:
					printf("\t%s","��  ��");
					break;
				case 5:
					printf("\t%s","��  ��");
					break;
				case 6:
					printf("\t%s","��  ��");
					break;
				default:
					break;
			}
			
			printf("%10d%14d��\t",ticketnumArr[i],ticketPriceArr[i]) ;
			
			switch (Special_OfferArr[i]) {
				case 1:
					printf("%s\n","��� ����.");
					break;
				case 2:
					printf("%s\n","����� ����");
					break;
				case 3:
					printf("%s\n","���������� ����");
					break;
				case 4:
					printf("%s\n","�ް��庴 ����");
					break;
				case 5:
					printf("%s\n","�ӻ�� ����");
					break;
				case 6:
					printf("%s\n","���ڳ� ����");
					break;
				default:
					break;
			}
		}
		printf("\nTOTAL PRICE :  %d�� �Դϴ�.", totalTicketPrice);
		printf("\n===================================================================================\n") ;
		printf("\n��� �ֹ��Ͻðڽ��ϱ�?\n1.YES\n2.NO\n");
		scanf("%d",&next);
		//���� �ʱ�ȭ 
		counter = 0;
		totalTicketPrice=0;
	} while(next == 1);
	return 0; 
} 
