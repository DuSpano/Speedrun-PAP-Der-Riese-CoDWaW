#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

#define PROCESS_NAME "CoDWaW.exe"
#define PLAYER_X_POSITION 0x18ED088
#define PLAYER_Y_POSITION 0x18ED08C
#define PLAYER_Z_POSITION 0x18ED090
#define POWER_X_LOCATION 536.284
#define POWER_Y_LOCATION -1802.49
#define POWER_Z_LOCATION 58.5989
#define TELEPORTER_HOME_X_LOCATION -53.5769
#define TELEPORTER_HOME_Y_LOCATION 303.439
#define TELEPORTER_HOME_Z_LOCATION 103.125
#define TELEPORTER_1_X_LOCATION -1780.58
#define TELEPORTER_1_Y_LOCATION -1121.46
#define TELEPORTER_1_Z_LOCATION 231.125
#define TELEPORTER_2_X_LOCATION 288.579
#define TELEPORTER_2_Y_LOCATION -3197.92
#define TELEPORTER_2_Z_LOCATION 189.125
#define TELEPORTER_3_X_LOCATION 1263.52
#define TELEPORTER_3_Y_LOCATION 1304.96
#define TELEPORTER_3_Z_LOCATION 200.125
#define POLL_RATE 100

DWORD get_process_id_by_process_name(const char* process_name_)
{
	PROCESSENTRY32 process_entry = { sizeof(PROCESSENTRY32) };
	HANDLE processes_snapshot;
	DWORD process_id = 0;

	//Achar o nome do processo
	processes_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(processes_snapshot, &process_entry))
	{
		do
		{
			if (!strcmp(process_entry.szExeFile, process_name_))
			{
				process_id = process_entry.th32ProcessID;
				break;
			}
		} while (Process32Next(processes_snapshot, &process_entry));
	}

	//Limpar os recursos
	CloseHandle(processes_snapshot);

	return process_id;
}

void move_player_location(HANDLE process_handle_, float x_position, float y_position, float z_position)
{
	WriteProcessMemory(process_handle_, (LPVOID)(PLAYER_X_POSITION), &x_position, sizeof(float), NULL);
	WriteProcessMemory(process_handle_, (LPVOID)(PLAYER_Y_POSITION), &y_position, sizeof(float), NULL);
	WriteProcessMemory(process_handle_, (LPVOID)(PLAYER_Z_POSITION), &z_position, sizeof(float), NULL);
}

void press_f_key()
{
	INPUT input;
	memset(&input, 0, sizeof(input));

	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VkKeyScan('f');
	SendInput(1, &input, sizeof(INPUT));
	Sleep(500);
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

int main(int argc_, char** argv_)
{
	//pegando o jogo
	std::cout << "Apegando o Jogo" << std::endl;
	DWORD process = NULL;
	while (process == NULL)
	{
		process = get_process_id_by_process_name(PROCESS_NAME);
	}
	HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process);

	//checando se conseguimos acesso no jogo
	if (process_handle != NULL)
	{
		std::cout << "Pegamos o Jogo." << std::endl;
		while (true)
		{
			//limpar a tela do menu
			system("cls");

			std::cout << "Ativando Speed Run Pack-A-Punch Hack" << std::endl;
			std::cout << "====================================" << std::endl;
			std::cout << "[F6] - Iniciando Speedrun PAP Hack" << std::endl;

			SHORT keypress = GetAsyncKeyState(VK_F6);
			if (keypress)
			{
				//Pegar original xyz local do player
				float player_x, player_y, player_z;
				ReadProcessMemory(process_handle, (LPVOID)(PLAYER_X_POSITION), &player_x, sizeof(float), NULL);
				ReadProcessMemory(process_handle, (LPVOID)(PLAYER_Y_POSITION), &player_y, sizeof(float), NULL);
				ReadProcessMemory(process_handle, (LPVOID)(PLAYER_Z_POSITION), &player_z, sizeof(float), NULL);

				//ir para o lugar da energia e ativar a energia
				move_player_location(process_handle, POWER_X_LOCATION, POWER_Y_LOCATION, POWER_Z_LOCATION);
				press_f_key();
				Sleep(1000);

				//va para o teleporte 1 e ative
				move_player_location(process_handle, TELEPORTER_1_X_LOCATION, TELEPORTER_1_Y_LOCATION, TELEPORTER_1_Z_LOCATION);
				Sleep(500);
				press_f_key();
				Sleep(1000);

				//va para o teleporte home e ative
				move_player_location(process_handle, TELEPORTER_HOME_X_LOCATION, TELEPORTER_HOME_Y_LOCATION, TELEPORTER_HOME_Z_LOCATION);
				Sleep(500);
				press_f_key();
				Sleep(10000);

				//va para o teleporte 2 e ative
				move_player_location(process_handle, TELEPORTER_2_X_LOCATION, TELEPORTER_2_Y_LOCATION, TELEPORTER_2_Z_LOCATION);
				Sleep(500);
				press_f_key();
				Sleep(1000);

				//va para o teleporte home e ative
				move_player_location(process_handle, TELEPORTER_HOME_X_LOCATION, TELEPORTER_HOME_Y_LOCATION, TELEPORTER_HOME_Z_LOCATION);
				Sleep(500);
				press_f_key();
				Sleep(10000);

				//va para o teleporte 3 e ative
				move_player_location(process_handle, TELEPORTER_3_X_LOCATION, TELEPORTER_3_Y_LOCATION, TELEPORTER_3_Z_LOCATION);
				Sleep(500);
				press_f_key();
				Sleep(1000);

				//va para o teleporte home e ative
				move_player_location(process_handle, TELEPORTER_HOME_X_LOCATION, TELEPORTER_HOME_Y_LOCATION, TELEPORTER_HOME_Z_LOCATION);
				Sleep(500);
				press_f_key();
				Sleep(10000);

				//voltar o jogador para o lugar que estava antes
				move_player_location(process_handle, player_x, player_y, player_z);
			}
			Sleep(POLL_RATE);
		}
	}
}