#include <stdio.h>
#include <string.h>

// 연락처 구조체 정의
#define MAX_NUM 100
struct address {
	char name[30 ];
	char age[5];
	char phone[15];
};

int count = 0;

void print_menu();
void view_juso(struct address* ptr);
void address_read(struct address* ptr);
void add_juso(struct address*ptr);
void find_juso(struct address*ptr);
void delete_juso();
void save_juso(struct address* ptr);

// 연락처 파일명을 전역변수로 고정
const char* fname = "c:\\temp\\juso.txt";

int main()
{
	struct address add_list[MAX_NUM];
	FILE* rfp, * wfp;

	rfp = fopen(fname, "r");

	// 만약, 연락처 파일이 없다면 빈파일을 만듦
	if (rfp == NULL)
	{
		wfp = fopen(fname, "w");
		fclose(wfp);
		rfp = fopen(fname, "r");
	}
	if (count == 1)
		puts("\n ** 연락처 파일에 전화번호가 하나도 없어요. **\n");

	address_read(add_list);
	char select = 0;
	puts(" \n### 친구 핸펀 Ver 2.0 ### \n");

	while (select != 5)
	{
		print_menu();
		select = getche();
		getchar();

		printf("\n");

		switch (select)
		{
		case '1': view_juso(add_list);
			break;
		case '2': add_juso(add_list);
			break;
		case '3': delete_juso();
			break;
		case '4': find_juso(add_list);
			break;
		case '5': save_juso(add_list);
			return 0;
			break;
		default: printf("\n 잘못 입력했어요. 다시 선택하세요.\n");
		}
	}

	return 0;
}

// 처음에 사용자의 선택을 위한 메뉴 출력
void print_menu()
{
	printf("\n");
	printf("1. 연락처 출력 \n");
	printf("2. 연락처 등록 \n");
	printf("3. 연락처 삭제 \n");
	printf("4. 연락처 검색 \n");
	printf("5. 끝내기 \n");
}

// 연락처 파일에서 기존 입력된 내용을 읽어서 출력
void view_juso(struct address* ptr)
{
	for (int i = 0; i < count; i++) 
	{
		printf("%d %s %s %s\n", i+1, ptr[i].name, ptr[i].age, ptr[i].phone);
	}
}

void address_read(struct address*ptr)
{
	FILE* rfp;

	rfp = fopen(fname, "r");

	for(int i=0;;i++)
	{
		
		fscanf(rfp, "%s\t%s\t%s\n", &ptr[i].name, &ptr[i].age, &ptr[i].phone);
		count += 1;
		
		if (feof(rfp))
			break;
	}
	if (count==0)
		puts("\n ** 연락처 파일에 전화번호가 하나도 없어요. **\n");

	fclose(rfp);
}

// 연락처를 추가
void add_juso(struct address* ptr)
{
	FILE* wfp;
	int i=0;
	char address_file[MAX_NUM][200];

	wfp = fopen(fname, "w");

	if (count < MAX_NUM)
	{
		printf("이름을 입력 ==>");
		gets(ptr[i+count].name);
		printf("나이를 입력 ==>");
		gets(ptr[i+count].age);
		printf("전화번호를 입력 ==>");
		gets(ptr[i+count].phone);
	}
	count += 1;

	struct address tmp;

		for (int i = 0; i <= count; i++)
		{
			for (int j = i + 1; j < count; j++)
				if (strcmp(ptr[j].name, ptr[i].name) < 0)
				{
					tmp = ptr[j];
					ptr[j] = ptr[i];
					ptr[i] = tmp;
				}
		}
	// 파일에 문자열 쓰기
		for (int i = 0; i < count; i++)
		{
			strcat(address_file[i], ptr[i].name);
			strcat(address_file[i], "\t");
			strcat(address_file[i], ptr[i].age);
			strcat(address_file[i], "\t");
			strcat(address_file[i], ptr[i].phone);
			strcat(address_file[i], "\n");
		}

		for (int i = 0; i < count; i++)
		{
			fputs(address_file[i], wfp);
		}
		fclose(wfp);
}

void find_juso(struct address* ptr)
{
	int find_index = 0;
	printf("검색할 주소의 인덱스를 입력하세요 : ");
	scanf("%d", &find_index);

	if ((find_index > 0) && (find_index < count + 1))
	{
		printf("\n----검색한 주소----\n");
		printf("%d : %s %s %s \n", find_index, ptr[find_index - 1].name, ptr[find_index - 1].age, ptr[find_index - 1].phone);
		printf("-------------------");
	}

	else
		printf("검색한 인덱스의 주소가 없습니다");
}

// 연락처 파일에서 선택한 연락처를 제거
void delete_juso()
{
	// 연락처 파일의 내용 전체를 저장하기 위한 2차원 배열
	char read_str[50][200] = { "", }; // 최대 연락처 개수를 50개로 가정

	char str[200] = "";
	FILE* rfp, * wfp;
	int del_line, i,count=0;

	rfp = fopen(fname, "r");

	// 연락처 파일이 없으면 돌아간다.
	if (rfp == NULL)
	{
		puts("\n!! 연락처 파일이 없습니다. !!\n");
		return;
	}

	printf("\n삭제할 행 번호는 ? ");
	scanf("%d", &del_line);

	/*struct address temp;

	for (int i = del_line; i <= count; i++)
	{
			if (count=del_line)
			{
				temp = ptr[del_line];
				ptr[del_line] = ptr[i+count];
				ptr[i+count] = temp;
			}
	}
	count--;*/

	for (i = 0; i < 50; i++)  // 파일에 있는 동안에 수행, 단 최대 50개
	{
		strcpy(str, "");
		fgets(str, 200, rfp);

		if (i + 1 != del_line)  // 삭제하는 행이 아니라면, 추가
		{
			strcpy(read_str[i], str);
			count++;
		}
		else
			printf("%d 행이 삭제되었습니다. \n", del_line);

		if (feof(rfp))
			break;
	}
	fclose(rfp);

	// 파일을 쓰기 모드로 열고, 새로운 내용을 쓴다.
	wfp = fopen(fname, "w");

	for (i = 0; i < count; i++)
		fputs(read_str[i], wfp);
	count -= 1;
	fclose(wfp);
}

void save_juso(struct address* ptr)
{
	FILE* wfp;

	wfp = fopen(fname, "w");

	for (int i = 0; i < count; i++) 
	{
		char save[200] = "";
		strcat(save, ptr[i].name);
		strcat(save, "\t");
		strcat(save, ptr[i].age);
		strcat(save, "\t");
		strcat(save, ptr[i].phone);
		strcat(save, "\n");

		fputs(save, wfp);
	}
	fclose(wfp);
}