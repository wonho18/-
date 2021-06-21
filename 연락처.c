#include <stdio.h>
#include <string.h>

// ����ó ����ü ����
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

// ����ó ���ϸ��� ���������� ����
const char* fname = "c:\\temp\\juso.txt";

int main()
{
	struct address add_list[MAX_NUM];
	FILE* rfp, * wfp;

	rfp = fopen(fname, "r");

	// ����, ����ó ������ ���ٸ� �������� ����
	if (rfp == NULL)
	{
		wfp = fopen(fname, "w");
		fclose(wfp);
		rfp = fopen(fname, "r");
	}
	if (count == 1)
		puts("\n ** ����ó ���Ͽ� ��ȭ��ȣ�� �ϳ��� �����. **\n");

	address_read(add_list);
	char select = 0;
	puts(" \n### ģ�� ���� Ver 2.0 ### \n");

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
		default: printf("\n �߸� �Է��߾��. �ٽ� �����ϼ���.\n");
		}
	}

	return 0;
}

// ó���� ������� ������ ���� �޴� ���
void print_menu()
{
	printf("\n");
	printf("1. ����ó ��� \n");
	printf("2. ����ó ��� \n");
	printf("3. ����ó ���� \n");
	printf("4. ����ó �˻� \n");
	printf("5. ������ \n");
}

// ����ó ���Ͽ��� ���� �Էµ� ������ �о ���
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
		puts("\n ** ����ó ���Ͽ� ��ȭ��ȣ�� �ϳ��� �����. **\n");

	fclose(rfp);
}

// ����ó�� �߰�
void add_juso(struct address* ptr)
{
	FILE* wfp;
	int i=0;
	char address_file[MAX_NUM][200];

	wfp = fopen(fname, "w");

	if (count < MAX_NUM)
	{
		printf("�̸��� �Է� ==>");
		gets(ptr[i+count].name);
		printf("���̸� �Է� ==>");
		gets(ptr[i+count].age);
		printf("��ȭ��ȣ�� �Է� ==>");
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
	// ���Ͽ� ���ڿ� ����
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
	printf("�˻��� �ּ��� �ε����� �Է��ϼ��� : ");
	scanf("%d", &find_index);

	if ((find_index > 0) && (find_index < count + 1))
	{
		printf("\n----�˻��� �ּ�----\n");
		printf("%d : %s %s %s \n", find_index, ptr[find_index - 1].name, ptr[find_index - 1].age, ptr[find_index - 1].phone);
		printf("-------------------");
	}

	else
		printf("�˻��� �ε����� �ּҰ� �����ϴ�");
}

// ����ó ���Ͽ��� ������ ����ó�� ����
void delete_juso()
{
	// ����ó ������ ���� ��ü�� �����ϱ� ���� 2���� �迭
	char read_str[50][200] = { "", }; // �ִ� ����ó ������ 50���� ����

	char str[200] = "";
	FILE* rfp, * wfp;
	int del_line, i,count=0;

	rfp = fopen(fname, "r");

	// ����ó ������ ������ ���ư���.
	if (rfp == NULL)
	{
		puts("\n!! ����ó ������ �����ϴ�. !!\n");
		return;
	}

	printf("\n������ �� ��ȣ�� ? ");
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

	for (i = 0; i < 50; i++)  // ���Ͽ� �ִ� ���ȿ� ����, �� �ִ� 50��
	{
		strcpy(str, "");
		fgets(str, 200, rfp);

		if (i + 1 != del_line)  // �����ϴ� ���� �ƴ϶��, �߰�
		{
			strcpy(read_str[i], str);
			count++;
		}
		else
			printf("%d ���� �����Ǿ����ϴ�. \n", del_line);

		if (feof(rfp))
			break;
	}
	fclose(rfp);

	// ������ ���� ���� ����, ���ο� ������ ����.
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