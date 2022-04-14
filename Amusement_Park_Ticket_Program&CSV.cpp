#include <stdio.h>
#include <time.h>
#include <stdbool.h>

	//������ ����A - �����̿��  
	const int A_BABY_PRICE = 15000,
	A_ADULT_DAY_PRICE = 62000, A_ADULT_NIGHT_PRICE = 50000,
	A_TEEN_DAY_PRICE = 54000, A_TEEN_NIGHT_PRICE = 43000,
	A_CHILD_DAY_PRICE = 47000, A_CHILD_NIGHT_PRICE = 36000,
	A_OLD_DAY_PRICE = 47000, A_OLD_NIGHT_PRICE = 36000;
	

	//������ ����B - ��ũ�̿��  
	const int B_BABY_PRICE = 15000,
	B_ADULT_DAY_PRICE = 59000, B_ADULT_NIGHT_PRICE = 47000,
	B_TEEN_DAY_PRICE = 52000, B_TEEN_NIGHT_PRICE = 41000,
	B_CHILD_DAY_PRICE = 46000, B_CHILD_NIGHT_PRICE = 35000,
	B_OLD_DAY_PRICE = 46000, B_OLD_NIGHT_PRICE = 35000;


	// �ֹε�Ϲ�ȣ �м�
	const long long int FULL_DIGIT = 10000000000000,
	FULL_DIGIT_MIN = 10000000000, 
	SEVEN_DIGIT = 1000000;
	const int TWO_DIGIT = 100, ONE_DIGIT = 10,
	OLD_GENERATION = 1900, NEW_GENERATION = 2000,
	MALE_OLD = 1, FEMALE_OLD = 2, MALE_NEW = 3, FEMALE_NEW = 4,
	BEFORE_BIRTH = 2, AFTER_BIRTH = 1;


	// ���̿� ���� ����
	const int MIN_BABY = 1, MIN_CHILD = 3, MIN_TEEN = 13, MIN_ADULT = 19,
	MAX_CHILD = 12, MAX_TEEN = 18, MAX_ADULT = 64;
	
	
	// ���̿� ���� �׷�
	const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;
	
	// ������
	const float DISABLE_DISCOUNT_RATE = 0.5, PAT_DISCOUNT_RATE = 0.5,
	MULTICHILD_DISCOUNT_RATE = 0.3, MI_DISCOUNT_RATE = 0.49,
	PREGNANT_DISCOUNT_RATE = 0.5;

	// �ִ� �ֹ���
	const int MAX_COUNT = 10, MIN_COUNT = 1;
		
	
	// �Լ� ���� 
	void errorMessagePrint();
	
	int inputTicketSelect();
	long long int inputCustomerIDNumber();
	int inputOrderCount();
	int inputDiscountSelect();
	void inputData(int* ticketSelect, long long int* customerIDNumber, int* orderCount, int* discountSelect);
	
	int calcAge(long long int customerIDNumber);
	int calcAgeGroup(int age);
	int calcPriceProcess(int age, int ticketSelect);
	int calcDiscount(int calcPrice, int discountSelect);
	int calcPriceResult(int calcPrice, int orderCount);
	int processIntergration(long long int customerIDNumber, int ticketSelect, int discountSelect, int orderCount, int priceResult, int *age);
	
	void saveOrderList(int ticketSelect, int age, int orderCount, int priceResult, int discountSelect, int *position, int(*orderList)[5]);
	
	void pricePrint(int priceResult);
	void orderPrint(int totalPrice, int* position, int(*orderList)[5]);
	void orderFilePrint(int totalPrice, int* position, int(*orderList)[5], int* filePosition);

	int orderContinue();

	
	//����
	
	int main() {
		int totalPrice = 0; // �ֹ� �Ѿ�
		int position = 0; //�ֹ� ���� �迭 Ž����
	 	int filePosition = 0; //���� ��� ù�� ����
		int reportPostition = 0;
		int orderList[100][5] = {0};
		int isExit = 0;
		
		do
		{
			
			while(true)
			{
					long long int customerIDNumber = 0; //�ֹι�ȣ
					int ticketSelect = 0, orderCount = 0, discountSelect = 0; //����, �ֹ�����, ������
					int priceResult = 0, age = 0; //����, ����
					int continueSelect = 0; // �̾ �ֹ� 
			
					
					inputData(&ticketSelect, &customerIDNumber, &orderCount, &discountSelect); //�Է��Լ� ȣ��
					priceResult = processIntergration(customerIDNumber, ticketSelect, discountSelect, orderCount, priceResult, &age); //��� ��� 
					
					saveOrderList(ticketSelect, age, orderCount, priceResult, discountSelect, &position, orderList); // �ֹ� ���� ����
					
					totalPrice += priceResult; // ��� �հ� ���
					
					pricePrint(priceResult); // ���� ���
					
					continueSelect = orderContinue(); // �̾ �ֹ����� �Է�
					
					if(continueSelect == 2) 
					{
						break;
					 } 
				}
				orderPrint(totalPrice, &position, orderList); // �ֹ� ���� ��� 
				orderFilePrint(totalPrice, &position, orderList, &filePosition);
				
				printf("��� ����(1: ���ο� �ֹ�, 2: ���α׷� ����): ");
				scanf("%d",&isExit);
				position = 0;
				totalPrice = 0;
				
		} while(isExit == 1);
		return 0;
		 
	} 
	
	//���� �Է�
	int inputTicketSelect() 
	{  
		int ticketSelect = 0;
		printf("������ �����ϼ���.\n1. �����̿�� - 1DAY\n2. �����̿�� - After4\n3. ��ũ�̿�� - 1DAY\n4. ��ũ�̿�� - After4\n-> ");
		while(true)
		{
			scanf("%d", &ticketSelect);
			if(ticketSelect == 1 || ticketSelect == 2 || ticketSelect == 3 || ticketSelect ==4) 
			{
				break;
			}
			else
			{
				errorMessagePrint();
			}
			getchar();
		}
		return ticketSelect;
	}
	
	//�ֹε�Ϲ�ȣ �Է� 
	long long int inputCustomerIDNumber()
	{
		long long int customerIDNumber = 0;
		printf("�ֹι�ȣ�� �Է��ϼ���.\n-> ");
		while(true)
		{
				scanf("%lld", &customerIDNumber);
				if((customerIDNumber >= FULL_DIGIT_MIN) && (customerIDNumber < FULL_DIGIT))
				{
					break;
				}
				else
				{
					errorMessagePrint();
				}
				getchar();
		}
		return customerIDNumber;
	}
	
	
	//�ֹ� ���� �Է�
	int inputOrderCount() 
	{
		int orderCount = 0;
		
		printf("��� �ֹ��Ͻðڽ��ϱ�? (�ִ� 10��)\n-> ");
		while(true)
		{
			scanf("%d", &orderCount);
			if((orderCount <= MAX_COUNT) && (orderCount >= MIN_COUNT))
			{
				break;
			}
			else
			{
				errorMessagePrint();
			}
			getchar();

		}		
		return orderCount;
	}
	
	//������ �Է�
	int inputDiscountSelect()
	{
		int discountSelect = 0;
		
		
		printf("�������� �����ϼ���.\n1. ����\n2. �����\n3. ����������\n3. ���ڳ�\n5.�ӻ��\n6. �ް��庴\n-> ");
		while(true)
		{
			scanf("%d", &discountSelect);
			if(discountSelect >=1 && discountSelect <= 5)
			{
				break;
			}
			else 
			{
				errorMessagePrint();
			}
			getchar();
		}
		return discountSelect;
	}

	//�Է� �Լ� ȣ��
	void inputData(int* ticketSelect, long long int* customerIDNumber, int* orderCount, int* discountSelect)
	{
		//���� �Է� 
		*ticketSelect = inputTicketSelect();
		//�ֹε�Ϲ�ȣ �Է�
		*customerIDNumber = inputCustomerIDNumber();
		//�ֹ� ���� �Է�
		*orderCount = inputOrderCount();
		//������ �Է�
		*discountSelect = inputDiscountSelect();
    } 

	//������ ���
	int calcAge(long long int customerIDNumber)
	{
		long int calcIDNumber = 0; //������� ���
		int customerYear = 0, customerMonth = 0, customerDay = 0; //������ �������
		int todayYear = 0, todayMonth = 0, todayDay = 0; //���� ��¥
		int type = 0; //������ ���� �� 2000��� ����
		int koreanAge = 0, age = 0;
		
		
		/* �ֹε�Ϲ�ȣ�� ������� ���� */
		customerIDNumber += FULL_DIGIT; 					// ���ڸ� ������ ���� �ش簪�� ������
		calcIDNumber = customerIDNumber / SEVEN_DIGIT;
		type = calcIDNumber % 10;							// ���ڸ��� ù ��ȣ 
		calcIDNumber  /= ONE_DIGIT;  
		customerDay = calcIDNumber % TWO_DIGIT; 			// �� 
		calcIDNumber /= TWO_DIGIT; 
		customerMonth = calcIDNumber % TWO_DIGIT; 			// �� 
		calcIDNumber /= TWO_DIGIT;
		customerYear = calcIDNumber % TWO_DIGIT;			// ����
		
		if((type == MALE_NEW) || (type == FEMALE_NEW))      // 2000�� ���� �»��� ��� 
		{
			customerYear += NEW_GENERATION; 
		}
		else
		{
			customerYear += OLD_GENERATION;
		}
		
		/* ���� ��¥�� ���ϱ� */
		time_t current;
		time(&current);
		struct tm* structTime;
		structTime = localtime(&current);
		
		/* ���� �� */
		todayYear = structTime->tm_year + OLD_GENERATION;
		todayMonth = structTime->tm_mon + 1;
		todayDay = structTime->tm_mday;
		
	
		koreanAge = todayYear - customerYear +1; // �ѱ��� ���� 
		
		
		/* ������ ��� */
		if((customerMonth < todayMonth) || ((customerMonth == todayMonth) && (customerDay <= todayDay))) 
		{
			age = koreanAge - AFTER_BIRTH;
		}
		else
		{
			age = koreanAge - BEFORE_BIRTH;
		}
		return age;
	}
	
	
	//���ɴ뺰 �з�
	int calcAgeGroup(int age)
	{
		if((age < MIN_CHILD))
		{
			return 1;
		}
		else if ((age >= MIN_CHILD) && (age <= MAX_CHILD))
		{
			return 2;
		}
		else if ((age >= MIN_TEEN) && (age <= MAX_TEEN))
		{
			return 3;
		}
		else if ((age >= MIN_ADULT) && (age <= MAX_ADULT))
		{
			return 4;
		}
		else if ((age >MAX_ADULT))
		{
			return 2;
		}
		
	}
	
	//�־߱ǰ� ���̿� ���� �ݾ� ���
	int calcPriceProcess(int age, int ticketSelect)
	{
		int calcPrice = 0;
		
		if(calcAgeGroup(age) == BABY)
		{
			calcPrice = A_BABY_PRICE, B_BABY_PRICE;
		}
		
		else if (calcAgeGroup(age) == CHILD) 
		{
			if(ticketSelect == 1)
			{
				calcPrice = A_CHILD_DAY_PRICE;
			}
			else if(ticketSelect == 2)
			{
				calcPrice = A_CHILD_NIGHT_PRICE; 
			}		
			else if(ticketSelect == 3)
			{
				calcPrice = B_CHILD_DAY_PRICE;
			}
			else if(ticketSelect == 4)
			{
				calcPrice = B_CHILD_NIGHT_PRICE;
			}
		}
		
		else if (calcAgeGroup(age) == TEEN)
		{
				if(ticketSelect == 1)
			{
				calcPrice = A_TEEN_DAY_PRICE;
			}
			else if(ticketSelect == 2)
			{
				calcPrice = A_TEEN_NIGHT_PRICE; 
			}		
			else if(ticketSelect == 3)
			{
				calcPrice = B_TEEN_DAY_PRICE;
			}
			else if(ticketSelect == 4)
			{
				calcPrice = B_TEEN_NIGHT_PRICE;
			}
		}
		
		else if (calcAgeGroup(age) == ADULT)
		{
				if(ticketSelect == 1)
			{
				calcPrice = A_ADULT_DAY_PRICE;
			}
			else if(ticketSelect == 2)
			{
				calcPrice = A_ADULT_NIGHT_PRICE; 
			}		
			else if(ticketSelect == 3)
			{
				calcPrice = B_ADULT_DAY_PRICE;
			}
			else if(ticketSelect == 4)
			{
				calcPrice = B_ADULT_NIGHT_PRICE;
			}
		}
		
		else if (calcAgeGroup(age) == OLD) 
		{
			if(ticketSelect == 1)
			{
				calcPrice =  A_OLD_DAY_PRICE;
			}
			else if(ticketSelect == 2)
			{
				calcPrice = A_OLD_NIGHT_PRICE; 
			}		
			else if(ticketSelect == 3)
			{
				calcPrice = B_OLD_DAY_PRICE;
			}
			else if(ticketSelect == 4)
			{
				calcPrice = B_OLD_NIGHT_PRICE;
			}
		}
		
		else
		{
			printf(" ");
		}
		return calcPrice;
	
	}
		
	//�����׿� ���� ���� ���
	int calcDiscount(int calcPrice, int discountSelect)
	{
		switch(discountSelect)
		{
		case 2 : // �����
				calcPrice *= DISABLE_DISCOUNT_RATE;
				break;
				 
		case 3 : //����������
				calcPrice *= PAT_DISCOUNT_RATE;
				break;	
				
		case 4 : //���ڳ� 
				calcPrice *= MULTICHILD_DISCOUNT_RATE;
				break;
		
		case 5 : //�ӻ�� 
				calcPrice *= PREGNANT_DISCOUNT_RATE;
				break;
					
		case 6 : //�ް��庴 
				calcPrice *= MI_DISCOUNT_RATE;
				break;
				
		default:
				break;
							
		}
		return calcPrice;
	}	

	//�ֹ� ������ ���� �ݾ� ���
	int calcPriceResult(int calcPrice, int orderCount) 
	{
		return calcPrice * orderCount;
	}
	
	//��� �Լ� ȣ��
	int processIntergration(long long int customerIDNumber, int ticketSelect, int discountSelect, int orderCount, int priceResult, int *age)
	{
		int calcPrice = 0;
		
		//�� ���� ��� 
		*age = calcAge(customerIDNumber);
		
		//�־߱ǰ� ���̿� ���� �ݾ� ���
		calcPrice  = calcPriceProcess(*age, ticketSelect);
		
		//�����׿� ���� ���� ��� 
		calcPrice = calcDiscount(calcPrice, discountSelect);
		
		//�ֹ� ������ ���� ���� �ݾ� ���
		priceResult = calcPriceResult(calcPrice, orderCount);
		
		return priceResult; //���� ��� ���� 
	} 
	
	//�ֹ� ���� ����
	void saveOrderList(int ticketSelect, int age, int orderCount, int priceResult, int discountSelect, int *position, int(*orderList)[5]) 
	{
		
		orderList[*position][0] = ticketSelect;
		orderList[*position][1] = age;
		orderList[*position][2] = orderCount;
		orderList[*position][3] = priceResult;
		orderList[*position][4] = discountSelect;
		(*position)++;
		
	}
	
	//Ƽ�� ���� ���
	void pricePrint(int priceResult)
	{
		printf("������ %d �� �Դϴ�. \n", priceResult);
		printf("THANK YOU! :)\n\n");
	}
	 
	//�ֹ� ���� ���
	void orderPrint(int totalPrice, int* position, int(*orderList)[5]) 
	{
		printf("Ƽ�� �߱��� �����մϴ�. �����մϴ�! \n");
		printf("\n");
		printf("================================ SH'S -- WORLD ================================\n");
				
		for(int index = 0; index < *position; index++)
		{
			switch(orderList[index][0])
			{
				case 1 : //���� - 1DAY
						printf("���� - 1DAY");
						break;

				case 2 : //���� - After4
						printf("���� - After4");
						break;				 

				case 3 : //���� - 1DAY
						printf("��ũ - 1DAY");
						break;

				case 4 : //���� - After4
						printf("��ũ - After4");
						break;

				default:
						break;
			}
			
			if(calcAgeGroup(orderList[index][1]) == BABY)
			{
				printf("����	");
			}
			else if(calcAgeGroup(orderList[index][1]) == CHILD)
			{
				printf("���	");
			}
			else if(calcAgeGroup(orderList[index][1]) == TEEN)
			{
				printf("û�ҳ�	");
			}
			else if(calcAgeGroup(orderList[index][1]) == ADULT)
			{
				printf("�	");
			}
 			else
 			{
 				printf("���	");
			}

			printf("X %3d", orderList[index][2]);
			printf("%8d��	", orderList[index][3]);
			
			switch(orderList[index][4])
			{
			case 1: //����
					printf("*������� ����\n");
					break; 
						
			case 2: //����� 
					printf("*����� �������\n");
					break; 						
												
			case 3: //���������� 
					printf("*���������� �������\n");
					break; 						
												
			case 4: //���ڳ� 
					printf("*���ڳ� �������\n");
					break;						
						
			case 5: //�ӻ�� 
					printf("*�ӻ�� �������\n");
					break; 						
						
			case 6: //�ް��庴 
					printf("*�ް��庴 �������\n");
					break; 						
						
			default:
					break;		
						
			} 
		}
		printf("\n");
		printf("����� �Ѿ��� %d�� �Դϴ�.\n", totalPrice);
		printf("====================================================================================");
	}
	
	
	
	//�ֹ� ���� ���Ϸ� ���
	void orderFilePrint(int totalPrice, int* position, int(*orderList)[5], int* filePosition)
	{
		FILE *fp = fopen("FLORENTINA_WORLD.csv", "a+");
		char temp ;
		
		
		/* ���� ��¥ ���ϱ� */
		time_t timer;
		struct tm* t;
		timer = time(NULL);
		t = localtime(&timer);
		
		for(int index = 0; index < *position; index++)
		{
			if(*filePosition == 0) //ù ���� ��� ��� 
			{
				if(fscanf(fp, "%c", &temp) == -1) //���Ͽ� ���ڰ� �������� ������ ���
				{
					fprintf(fp, "��¥,	����,	���ɱ���,	����,	����,	������\n"); 
				 } 
			}
			(*filePosition)++;
			fprintf(fp, "%d%02d%02d,",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
			
			
			switch(orderList[index][0])
			{
			case 1 : //���� - 1DAY
					printf("\n���� - 1DAY\n");
					break;

			case 2 : //���� - After4
					printf("\n���� - After4\n");
					break;				 

			case 3 : //���� - 1DAY
					printf("\n��ũ - 1DAY\n");
					break;

			case 4 : //���� - After4
					printf("\n��ũ - After4\n");
					break;

			default:
					break;
			}
			
			if(calcAgeGroup(orderList[index][1]) == BABY) 
			{
				fprintf(fp, "���� ,");
			}
			else if(calcAgeGroup(orderList[index][1]) == CHILD) 
			{
				fprintf(fp, "��� ,");
			} 
			else if(calcAgeGroup(orderList[index][1]) == TEEN) 
			{
				fprintf(fp, "û�ҳ� ,");
			}	
			else if(calcAgeGroup(orderList[index][1]) == ADULT) 
			{
				fprintf(fp, "� ,");
			}	
			else
			{
				fprintf(fp, "���� ,");
			}
			
			fprintf(fp, "%d,", orderList[index][2]);
			fprintf(fp, "%d,", orderList[index][3]);
			
			switch(orderList[index][4])
			{
			case 1: //����
					printf("*������� ����\n\n");
					break; 
						
			case 2: //����� 
					printf("*����� �������\n\n");
					break; 						
												
			case 3: //���������� 
					printf("*���������� �������\n\n");
					break; 						
												
			case 4: //���ڳ� 
					printf("*���ڳ� �������\n\n");
					break;						
						
			case 5: //�ӻ�� 
					printf("*�ӻ�� �������\n\n");
					break; 						
						
			case 6: //�ް��庴 
					printf("*�ް��庴 �������\n\n");
					break; 						
						
			default:
					break;	
			}	
		 } 
		 fclose(fp);
	}
	
	//�̾ �ֹ� or �ֹ����� ��� �� ����
	int orderContinue()
	{
		int continueSelect = 0;
		
		printf("��� �߱��Ͻðڽ��ϱ�?\n");
		printf("1. Ƽ�� �߱�\n");
		printf("2. ����\n");
		while(true)
		{
			scanf("%d", &continueSelect);
			if(continueSelect == 1 || continueSelect == 2)
			{
				break;	
			}
			else
			{
				errorMessagePrint();	
			}	
			getchar();
		} 
		return continueSelect;

	}
	
	
	//�����޽��� ���
	void errorMessagePrint()
	{
	  	printf("�߸� �Է��ϼ̽��ϴ�.\n");	
	} 

