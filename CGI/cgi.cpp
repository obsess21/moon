//�ܵ�
//ʹ�ã��������ܵ�ʵ��ͨ��
#include <stdio.h>
#include <Windows.h>

int main(void) {
	//�����ܵ�
	HANDLE output[2];
	
	SECURITY_ATTRIBUTES la;
	la.nLength = sizeof(la);
	la.bInheritHandle = true;//�̳�
	la.lpSecurityDescriptor = 0;//��ȫ���� 0Ĭ��ֵ



	BOOL bCreate = CreatePipe(&output[0], &output[1], &la, 0);
	if (bCreate == false) {
		MessageBox(0, "create cgi pipe error!", 0, 0);
		return 1;
	}
	//�����ӽ���
	char cmd[] = "ping www.baidu.com";

	//�ӽ���������Ϣ
	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	si.hStdInput = output[1];//�ܵ�д��
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi = { 0 };

	bCreate = CreateProcess(NULL,cmd,0,0,TRUE,0,0,0,&si,&pi);
	if (bCreate == false) {
		printf("���̴���ʧ��!\n");
		return 1;
	}

	char buff[1024];
	DWORD size;
	while (1) {
		/*printf("�����룺");
		gets_s(buff, sizeof(buff));

		WriteFile(output[1], buff, sizeof(buff) + 1, &size,NULL);
		printf("�Ѿ�д����%d�ֽ�\n", size);*/


		ReadFile(output[0], buff, sizeof(buff), &size, NULL);
		buff[size] = '\0';
		printf("�Ѿ�������%d���ֽڣ�[%s]", size, buff);
	


	}

}