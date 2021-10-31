#include <iostream>
#include <filesystem>
#include "DxLib.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>
#include <stdexcept>



std::vector<std::string> getImageName(std::string dir_name) {

	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> file_names;

	// png,jpg,bmpの拡張子のファイルのみを読み込む
	std::string extension[1] = { "txt" };

	for (int i = 0; i < 1; i++) {

		std::string search_name = dir_name + "*." + extension[i];
		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) {
			continue;
		}
		do {
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			}
			else {
				file_names.push_back(win32fd.cFileName);
			}
		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);
	}
	return file_names;
}


// プログラムは WinMain から始まります  
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	int combo = 0;				//コンボ
	std::vector<double> bpm;
	std::vector<int> bpm_mea;
	double LLine, RLine;

	LONGLONG start_time = 0; //開始した時刻
	LONGLONG now_time; //現在のフレームの時刻
	__int64 currentTime; //開始してからの経過時間
	__int64 counter = -1;

	SetMainWindowText("prsk studio");	//ウインドウのタイトルを設定
	ChangeWindowMode(true);				//ウインドウモードで起動
	SetGraphMode(1280, 720, 32);		//ウインドウサイズ変更
	SetAlwaysRunFlag(true);				//バックグラウンド再生可

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	int back = LoadGraph("images/back.png");	//画像読み込み
	int bg_bk = LoadGraph("images/bg_bk.png");
	int line = LoadGraph("images/line.png");
	int gauge = LoadGraph("images/scoreGauge.png");
	int perfect = LoadGraph("images/perfect.png");
	int title_image = LoadGraph("images/tex_title_bg_01.png");
	int title_txt_press = LoadGraph("images/tex_title_press.png");
	int title_txt = LoadGraph("images/title_text.png");
	int jacket_back = LoadGraph("images/c034ec.png");
	int text_master = LoadGraph("images/text_master.png");
	int light = LoadGraph("images/light.png");
	int now_loading = LoadGraph("images/now_loading.png");

	int combonum[10];
	combonum[0] = LoadGraph("images/text_combo_0.png");
	combonum[1] = LoadGraph("images/text_combo_1.png");
	combonum[2] = LoadGraph("images/text_combo_2.png");
	combonum[3] = LoadGraph("images/text_combo_3.png");
	combonum[4] = LoadGraph("images/text_combo_4.png");
	combonum[5] = LoadGraph("images/text_combo_5.png");
	combonum[6] = LoadGraph("images/text_combo_6.png");
	combonum[7] = LoadGraph("images/text_combo_7.png");
	combonum[8] = LoadGraph("images/text_combo_8.png");
	combonum[9] = LoadGraph("images/text_combo_9.png");
	int combotxt = LoadGraph("images/text_combo.png");

	int Nnote_l = LoadGraph("images/note_left.PNG");	//ノーツ読み込み
	int Nnote_c = LoadGraph("images/note_center2.PNG");
	int Nnote_r = LoadGraph("images/note_right.PNG");

	int Cnote_l = LoadGraph("images/Cnote_left.PNG");
	int Cnote_c = LoadGraph("images/Cnote_center2.PNG");
	int Cnote_r = LoadGraph("images/Cnote_right.PNG");

	int Fnote_l = LoadGraph("images/Fnote_left.PNG");
	int Fnote_c = LoadGraph("images/Fnote_center2.PNG");
	int Fnote_r = LoadGraph("images/Fnote_right.PNG");
	int Fnote_ar[6][2];
	Fnote_ar[0][0] = LoadGraph("images/notes_flick_arrow_01.png");
	Fnote_ar[1][0] = LoadGraph("images/notes_flick_arrow_02.png");
	Fnote_ar[2][0] = LoadGraph("images/notes_flick_arrow_03.png");
	Fnote_ar[3][0] = LoadGraph("images/notes_flick_arrow_04.png");
	Fnote_ar[4][0] = LoadGraph("images/notes_flick_arrow_05.png");
	Fnote_ar[5][0] = LoadGraph("images/notes_flick_arrow_06.png");
	Fnote_ar[0][1] = LoadGraph("images/notes_flick_arrow_01_diagonal_left.png");
	Fnote_ar[1][1] = LoadGraph("images/notes_flick_arrow_02_diagonal_left.png");
	Fnote_ar[2][1] = LoadGraph("images/notes_flick_arrow_03_diagonal_left.png");
	Fnote_ar[3][1] = LoadGraph("images/notes_flick_arrow_04_diagonal_left.png");
	Fnote_ar[4][1] = LoadGraph("images/notes_flick_arrow_05_diagonal_left.png");
	Fnote_ar[5][1] = LoadGraph("images/notes_flick_arrow_06_diagonal_left.png");

	int CFnote_ar[6][2];
	CFnote_ar[0][0] = LoadGraph("images/notes_flick_arrow_crtcl_01.png");
	CFnote_ar[1][0] = LoadGraph("images/notes_flick_arrow_crtcl_02.png");
	CFnote_ar[2][0] = LoadGraph("images/notes_flick_arrow_crtcl_03.png");
	CFnote_ar[3][0] = LoadGraph("images/notes_flick_arrow_crtcl_04.png");
	CFnote_ar[4][0] = LoadGraph("images/notes_flick_arrow_crtcl_05.png");
	CFnote_ar[5][0] = LoadGraph("images/notes_flick_arrow_crtcl_06.png");
	CFnote_ar[0][1] = LoadGraph("images/notes_flick_arrow_crtcl_01_diagonal_left.png");
	CFnote_ar[1][1] = LoadGraph("images/notes_flick_arrow_crtcl_02_diagonal_left.png");
	CFnote_ar[2][1] = LoadGraph("images/notes_flick_arrow_crtcl_03_diagonal_left.png");
	CFnote_ar[3][1] = LoadGraph("images/notes_flick_arrow_crtcl_04_diagonal_left.png");
	CFnote_ar[4][1] = LoadGraph("images/notes_flick_arrow_crtcl_05_diagonal_left.png");
	CFnote_ar[5][1] = LoadGraph("images/notes_flick_arrow_crtcl_06_diagonal_left.png");

	int Lnote_l = LoadGraph("images/Lnote_left.PNG");
	int Lnote_c = LoadGraph("images/Lnote_center2.PNG");
	int Lnote_r = LoadGraph("images/Lnote_right.PNG");
	int Lnote_a = LoadGraph("images/2notes_long_among.png");
	int CLnote_a = LoadGraph("images/cnotes_long_among.png");
	int Lnote_m = LoadGraph("images/long_m.png");
	int CLnote_m = LoadGraph("images/c_long_m.png");

	int effect = LoadGraph("images/tex_note_common_all.png");
	int tap_effect = DerivationGraph(960, 128, 64, 128, effect);
	int tap_effect2 = DerivationGraph(640, 0, 128, 128, effect);
	int critical_effect = DerivationGraph(960, 384, 64, 128, effect);
	int critical_effect2 = DerivationGraph(640, 256, 128, 128, effect);
	int flick_effect = DerivationGraph(704, 640, 64, 128, effect);
	int flick_effect3 = DerivationGraph(512, 640, 128, 128, effect);
	int long_effect = DerivationGraph(448, 640, 64, 128, effect);
	int long_effect2 = DerivationGraph(128, 512, 128, 128, effect);
	int long_effect3 = DerivationGraph(256, 640, 128, 128, effect);

	int flick_effect2 = DerivationGraph(896, 512, 128, 256, effect);
	int cflick_effect2 = DerivationGraph(896, 768, 128, 256, effect);

	int normal_notes_sound = LoadSoundMem("sounds/normal_notes.mp3", 8);	//SE読み込み
	int critical_notes_sound = LoadSoundMem("sounds/critical_notes.mp3", 8);
	int normal_flick_sound = LoadSoundMem("sounds/normal_flick.mp3", 8);
	int critical_flick_sound = LoadSoundMem("sounds/critical_flick.mp3", 8);
	int long_among_sound = LoadSoundMem("sounds/long_among.mp3", 8);
	int long_sound = LoadSoundMem("sounds/long.mp3");
	int c_long_sound = LoadSoundMem("sounds/critical_long.mp3");

	int start = LoadSoundMem("sounds/start.mp3");

	int hold_m_sc[16];
	for (int i = 0; 16 > i; i++) {
		hold_m_sc[i] = MakeScreen(1280, 720, true);
	}

	DrawGraph(0, 0, title_image, true);
	DrawRotaGraph(640, 540, 0.1, 0, title_txt_press, true);
	DrawRotaGraph(450, 260, 0.4, 0, title_txt, true);

	WaitKey();

	std::vector<std::string> scorefilenames = getImageName("scorefile/");
	std::vector<std::string> musicname;
	int music_total = 0;
	for (int i = 0; scorefilenames.size() > i; i++) {
		musicname.resize(i + 1);
		musicname[i] = scorefilenames[i].substr(0, scorefilenames[i].length() - 4);

		music_total++;
	}

	int music_select_back = LoadGraph("images/music_select_back.jpeg");

	int f = 100000000;

	int mnf = CreateFontToHandle("FOT-ロダンNTLG Pro DB", 30, 1, DX_FONTTYPE_ANTIALIASING_8X8);
	int mnf2 = CreateFontToHandle("FOT-ロダンNTLG Pro DB", 20, 1, DX_FONTTYPE_ANTIALIASING_8X8);

	while (CheckHitKey(KEY_INPUT_RETURN) == 1) {}

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		std::string jacket_d = "jacket_image/" + musicname[f % music_total] + ".png";
		int jacket = LoadGraph(jacket_d.c_str());

		DrawGraph(0, 0, title_image, true);
		DrawRotaGraph(319, 360, 0.44, 0, music_select_back, true);
		DrawExtendGraph(637, 38, 1280, 682, jacket, true);

		DrawStringToHandle(100, 345, musicname[f % music_total].c_str(), GetColor(255, 255, 255), mnf);
		DrawStringToHandle(100, 245, musicname[(f + 1) % music_total].c_str(), GetColor(255, 255, 255), mnf2);
		DrawStringToHandle(100, 145, musicname[(f + 2) % music_total].c_str(), GetColor(255, 255, 255), mnf2);
		DrawStringToHandle(100, 45, musicname[(f + 3) % music_total].c_str(), GetColor(255, 255, 255), mnf2);
		DrawStringToHandle(100, 475, musicname[(f - 1) % music_total].c_str(), GetColor(255, 255, 255), mnf2);
		DrawStringToHandle(100, 575, musicname[(f - 2) % music_total].c_str(), GetColor(255, 255, 255), mnf2);
		DrawStringToHandle(100, 675, musicname[(f - 3) % music_total].c_str(), GetColor(255, 255, 255), mnf2);

		if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
			break;
		}

		if (CheckHitKey(KEY_INPUT_UP) == 1) {
			f++;
			WaitTimer(100);
		}
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
			f--;
			WaitTimer(100);
		}
	}

	ClearDrawScreen();

	DrawExtendGraph(0, 0, 1281, 721, now_loading, true);

	std::string jkim = "jacket_image/" + musicname[f % music_total] + ".png";

	int jacket = LoadGraph(jkim.c_str());
	int imS;
	GetGraphSize(jacket, &imS, &imS);
	int jacketR = DerivationGraph(imS * 2 / 3, imS / 4, imS / 3, imS / 4, jacket);
	int jacketL = DerivationGraph(0, imS / 2, imS / 3, imS / 4, jacket);

	std::string ms = "songs/" + musicname[f % music_total] + ".mp3";
	int music = LoadSoundMem(ms.c_str());	//音楽読み込み

	std::string sc = "scorefile/" + musicname[f % music_total] + ".txt";
	std::ifstream scorefile;	//譜面読み込み
	scorefile.open(sc.c_str());

	int score_buffer;
	std::string score_buffer2;
	std::string score_buffer3;

	std::vector<std::string> scorecode2;
	std::vector<std::vector<std::string>> scorenum2;
	std::vector<int> mea2;

	int bpmC = 0, bpmC2 = 0,  y = 0, z = 0;
	scorecode2.resize(1);
	scorenum2.resize(1);
	scorenum2[0].resize(2);
	mea2.resize(1);

	//譜面ファイルの読み込み
	bool bpmGL = false;
	while (std::getline(scorefile, score_buffer2)) {
		if (z == 15) {
			bpm.resize(1);
			bpm[0] = stod(score_buffer2.substr(8));
			bpmGL = true;
			bpmC++;
		}
		else if (bpmGL) {
			if (score_buffer2.substr(0, 4) == "#BPM") {
				bpm.resize(bpmC + 1);
				bpm[bpmC] = stod(score_buffer2.substr(8));
				bpmC++;
			}
			else {
				bpmGL = false;
			}
		}

		if (15 + bpmC <= z && z <= 15 + bpmC * 2 - 1) {
			bpm_mea.resize(bpmC2 + 1);
			bpm_mea[bpmC2] = atoi(score_buffer2.substr(1, 3).c_str());
			bpmC2++;
		}

		if (19 + bpmC * 2 < z) {
			scorecode2.resize(y + 1);
			scorenum2.resize(y + 1);
			for (int i = 0; y + 1 > i; i++) {
				scorenum2[i].resize(2);
			}
			mea2.resize(y + 1);

			scorecode2[y] = score_buffer2;
			scorecode2[y].erase(scorecode2[y].begin() + 0);
			int c_pos = scorecode2[y].find(":");
			scorenum2[y][0] = scorecode2[y].substr(0, c_pos);
			scorenum2[y][1] = scorecode2[y].substr(c_pos + 1);
			std::string mea_buffer2 = scorenum2[y][0].substr(0, 3);
			mea2[y] = atoi(mea_buffer2.c_str());

			y++;
		}

		z++;
	}

	const int scoreline = mea2.size();

	double offset = 0;

	printfDx("%lf\n", bpm[0]);
	printfDx("%lf\n", bpm[1]);

	//譜面情報の並び替え
	int tmp2; std::string tmp3;
	for (int i = 0; scoreline > i; i++) {
		for (int j = i + 1; scoreline > j; j++) {
			if (mea2[i] > mea2[j]) {

				tmp2 = mea2[i];
				mea2[i] = mea2[j];
				mea2[j] = tmp2;


				tmp3 = scorenum2[i][0];
				scorenum2[i][0] = scorenum2[j][0];
				scorenum2[j][0] = tmp3;

				tmp3 = scorenum2[i][1];
				scorenum2[i][1] = scorenum2[j][1];
				scorenum2[j][1] = tmp3;

			}
		}
	}

	std::vector<std::vector<double>> noteinfo;
	std::vector<int> notekinds;
	std::vector<int> holdnum;

	int d = -1, n = 0, o = 0;
	double mea_t_ad = 0;
	//譜面ファイル情報からノーツ情報を読み取る
	for (int i = 0; mea2[scoreline - 1] >= i; i++) {
		for (int k = n; mea2[k] == i; k++) {
			
			if (bpm_mea.size() > d + 1) {
				if (bpm_mea[d + 1] == mea2[k]) {
					d++;
				}
			}
			
			for (int m = 0; scorenum2[n][1].size() / 2 > m; m++) {

				score_buffer2 = scorenum2[n][1].substr(m * 2, 2);
				score_buffer3 = score_buffer2;

				score_buffer = strtol(score_buffer2.c_str(), NULL, 16);

				if (score_buffer != 0) {

					noteinfo.resize(o + 1);
					noteinfo[o].resize(3);

					noteinfo[o][0] = (double)m / (double)scorenum2[n][1].size() * 2.0 * 240.0 / bpm[d] + mea_t_ad;	//ノーツのタイミング計算

					score_buffer2 = scorenum2[n][0].substr(4, 1);
					noteinfo[o][1] = strtol(score_buffer2.c_str(), NULL, 16);												//ノーツの左端の位置

					noteinfo[o][2] = strtol(score_buffer3.substr(1).c_str(), NULL, 16);													//ノーツの長さ

					notekinds.resize(o + 1);
					holdnum.resize(o + 1);

					if (atoi(scorenum2[n][0].substr(3, 1).c_str()) == 1) {					//通常ノーツ：1　黄ノーツ：2
						if (atoi(score_buffer3.substr(0, 1).c_str()) == 1) {
							notekinds[o] = 1;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 2) {
							notekinds[o] = 2;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 3) {
							notekinds[o] = 18;
						}
					}

					if (atoi(scorenum2[n][0].substr(3, 1).c_str()) == 3) {					//ホールド開始：6　有形中継点：7　無形中継点：8　終了：9
						if (atoi(score_buffer3.substr(0, 1).c_str()) == 1) {
							notekinds[o] = 6;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 3) {
							notekinds[o] = 7;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 5) {
							notekinds[o] = 8;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 2) {
							notekinds[o] = 9;
						}

						holdnum[o] = strtol(scorenum2[n][0].substr(5).c_str(), NULL, 16);
					}

					if (atoi(scorenum2[n][0].substr(3, 1).c_str()) == 5) {					//上フリック：3　左フリック：4　右フリック：5　黄上フリック：10　黄左フリック：11　黄右フリック：12
						if (atoi(score_buffer3.substr(0, 1).c_str()) == 1) {				//振り下ろし：13　左右振り下ろし：14

							notekinds[o] = 15;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 3) {
							notekinds[o] = 16;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 4) {
							notekinds[o] = 17;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 2) {
							notekinds[o] = 13;
						}
						else if (atoi(score_buffer3.substr(0, 1).c_str()) == 5 || atoi(score_buffer3.substr(0, 1).c_str()) == 6) {
							notekinds[o] = 14;
						}
					}
					o++;
				}
			}
			n++;
			if (mea2.size() <= n) {
				break;
			}

		}
		mea_t_ad += (double)240 / bpm[d]; 
		//printfDx("%lf\n", mea_t_ad);
	}

	const int note = o;	//ノーツの総数

	std::vector<bool> note_f;	//ノーツの存在フラグ
	std::vector<float> note_y;	//ノーツのy座標
	std::vector<double> note_m;	//ノーツの倍率
	note_f.resize(note);
	note_y.resize(note);
	note_m.resize(note);
	for (int j = 0; j < note; j++) {
		note_f[j] = false;	//すべてにfalseを代入

	}

	std::vector<int> hold_an;
	std::vector<int> hold_color;
	std::vector<int> hold_uf;
	hold_an.resize(note);
	hold_color.resize(note);
	hold_uf.resize(note);
	for (int i = 0; note > i; i++) {
		hold_an[i] = 0;
		hold_color[i] = 0;
		hold_uf[i] = 0;
	}

	//ノーツ情報の並び替え
	double tmp;
	for (int r = 0; note > r; r++) {
		for (int s = r + 1; note > s; s++) {
			if (noteinfo[r][0] > noteinfo[s][0]) {

				tmp = noteinfo[r][0];
				noteinfo[r][0] = noteinfo[s][0];
				noteinfo[s][0] = tmp;

				tmp = noteinfo[r][1];
				noteinfo[r][1] = noteinfo[s][1];
				noteinfo[s][1] = tmp;

				tmp = noteinfo[r][2];
				noteinfo[r][2] = noteinfo[s][2];
				noteinfo[s][2] = tmp;

				tmp2 = notekinds[r];
				notekinds[r] = notekinds[s];
				notekinds[s] = tmp2;

				tmp2 = holdnum[r];
				holdnum[r] = holdnum[s];
				holdnum[s] = tmp2;
			}
		}
	}

	//表示しないノーツを消す
	for (int i = 0; note > i; i++) {
		if (notekinds[i] == 15) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 1) {
						notekinds[j] = 3;

						notekinds[i] = 0;
					}
				}
			}
		}
		if (notekinds[i] == 16) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 1) {
						notekinds[j] = 4;

						notekinds[i] = 0;
					}
				}
			}
		}
		if (notekinds[i] == 17) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 1) {
						notekinds[j] = 5;

						notekinds[i] = 0;
					}
				}
			}
		}

		if (notekinds[i] == 15) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 2) {
						notekinds[j] = 10;

						notekinds[i] = 0;
					}
				}
			}
		}
		if (notekinds[i] == 16) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 2) {
						notekinds[j] = 11;

						notekinds[i] = 0;
					}
				}
			}
		}
		if (notekinds[i] == 17) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 2) {
						notekinds[j] = 12;

						notekinds[i] = 0;
					}
				}
			}
		}

	}

	for (int i = 0; note > i; i++) {
		if (notekinds[i] == 13) {
			for (int j = 0; note > j; j++) {
				if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && (notekinds[j] == 6 || notekinds[j] == 7 || notekinds[j] == 8 || notekinds[j] == 9)) {
					for (int k = 0; note > k; k++) {
						if (noteinfo[i][0] == noteinfo[k][0] && noteinfo[i][1] == noteinfo[k][1] && noteinfo[i][2] == noteinfo[k][2] && notekinds[k] == 1) {

							notekinds[i] = 0;

							notekinds[k] = 0;

							hold_an[j] = 1;
						}

					}
				}
			}
		}
		if (notekinds[i] == 14) {
			for (int j = 0; note > j; j++) {
				if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && (notekinds[j] == 6 || notekinds[j] == 7 || notekinds[j] == 8 || notekinds[j] == 9)) {
					for (int k = 0; note > k; k++) {
						if (noteinfo[i][0] == noteinfo[k][0] && noteinfo[i][1] == noteinfo[k][1] && noteinfo[i][2] == noteinfo[k][2] && notekinds[k] == 1) {

							notekinds[i] = 0;

							notekinds[k] = 0;

							hold_an[j] = 2;
						}
					}
				}
			}
		}

		if (notekinds[i] == 6) {
			for (int j = 0; note > j; j++) {
				if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 2) {

					notekinds[j] = 0;

					hold_color[i] = 1;

					for (int k = 0; note > k; k++) {
						if (noteinfo[i][0] == noteinfo[k][0] && noteinfo[i][1] == noteinfo[k][1] && noteinfo[i][2] == noteinfo[k][2] && notekinds[k] == 13) {

							notekinds[k] = 0;

							hold_an[i] = 1;
						}
						if (noteinfo[i][0] == noteinfo[k][0] && noteinfo[i][1] == noteinfo[k][1] && noteinfo[i][2] == noteinfo[k][2] && notekinds[k] == 14) {

							notekinds[k] = 0;

							hold_an[i] = 2;
						}
					}
				}
			}
		}
		if (notekinds[i] == 7 || notekinds[i] == 8) {
			for (int j = 0; note > j; j++) {
				if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 18) {

					notekinds[j] = 0;

					hold_uf[i] = 1;
				}
			}
		}
	}

	//ノーツ情報の並び替え
	for (int r = 0; note > r; r++) {
		for (int s = r + 1; note > s; s++) {
			if (noteinfo[r][0] > noteinfo[s][0]) {

				tmp = noteinfo[r][0];
				noteinfo[r][0] = noteinfo[s][0];
				noteinfo[s][0] = tmp;

				tmp = noteinfo[r][1];
				noteinfo[r][1] = noteinfo[s][1];
				noteinfo[s][1] = tmp;

				tmp = noteinfo[r][2];
				noteinfo[r][2] = noteinfo[s][2];
				noteinfo[s][2] = tmp;

				tmp2 = notekinds[r];
				notekinds[r] = notekinds[s];
				notekinds[s] = tmp2;

				tmp2 = holdnum[r];
				holdnum[r] = holdnum[s];
				holdnum[s] = tmp2;

				tmp2 = hold_an[r];
				hold_an[r] = hold_an[s];
				hold_an[s] = tmp2;

				tmp2 = hold_color[r];
				hold_color[r] = hold_color[s];
				hold_color[s] = tmp2;

				tmp2 = hold_uf[r];
				hold_uf[r] = hold_uf[s];
				hold_uf[s] = tmp2;
			}
		}
	}

	std::vector<double> hold_m_info;
	std::vector<int> hold_m_num;
	std::vector<double> hold_m_leftpos;
	std::vector<double> hold_m_width;

	std::vector<double> hold_m_long;
	std::vector<bool> hold_m_f;
	std::vector<float> hold_m_y;
	std::vector<double> hold_m_m;

	std::vector<bool> hold_s_f;
	std::vector<int> holf_m_num;
	std::vector<int> hold_m_color;

	std::vector<int> uf_pos;
	std::vector<int> uf_num;

	//ホールドの真ん中の部分の計算
	int c = 0, i = 0, uf_c = 0;;
	bool rep = false;
	int interval = 128;
	for (int j = 0; note > j; j++) {

		if (notekinds[j] == 6) {
			i = j;


			while (true) {
				i++;
				if (holdnum[j] == holdnum[i]) {
					if (notekinds[i] == 7 || notekinds[i] == 8) {
						if (hold_uf[i] == 1) {

							hold_color[i] = hold_color[j];
							uf_pos.resize(uf_c + 1);
							uf_pos[uf_c] = i;
							uf_num.resize(uf_c + 1);
							uf_num[uf_c] = holdnum[j];

							uf_c++;
						}
						else {
							rep = true;

							break;
						}
					}
					if (notekinds[i] == 9) {
						break;
					}
				}
			}

			hold_color[i] = hold_color[j];

			double hold_long = noteinfo[i][0] - noteinfo[j][0];
			int k = hold_long * 4 * interval;

			if (notekinds[i] == 9) {
				k -= 7;
			}
			else if (notekinds[i] == 7 || notekinds[i] == 8) {
				k += 1;
			}


			if (hold_an[j] == 0) {
				for (int l = 0; k > l; l++) {
					hold_m_info.resize(c + 1);
					hold_m_info[c] = noteinfo[j][0] + ((double)60 / (double)240 / (double)interval) * ((double)l + (double)1);

					hold_m_leftpos.resize(c + 1);
					hold_m_leftpos[c] = ((noteinfo[i][1] - noteinfo[j][1])) / (double)k * (double)l + (noteinfo[j][1] - (double)8);

					hold_m_width.resize(c + 1);
					hold_m_width[c] = ((noteinfo[i][2] - noteinfo[j][2])) / (double)k * (double)l + noteinfo[j][2];

					hold_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[i];

					holf_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[j];

					hold_m_color.resize(c + 1);
					hold_m_color[c] = hold_color[j];

					c++;
				}
			}
			else if (hold_an[j] == 1) {
				for (int l = 0; k > l; l++) {
					hold_m_info.resize(c + 1);
					hold_m_info[c] = noteinfo[j][0] + ((double)60 / (double)240 / (double)interval) * ((double)l + (double)1);

					hold_m_leftpos.resize(c + 1);
					hold_m_leftpos[c] = (noteinfo[i][1] - noteinfo[j][1]) / pow(k, 2.0) * pow(l + 1, 2.0) + noteinfo[j][1] - (double)8;

					hold_m_width.resize(c + 1);
					hold_m_width[c] = (noteinfo[i][2] - noteinfo[j][2]) / pow(k, 2.0) * pow(l + 1, 2.0) + noteinfo[j][2];

					hold_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[j];

					holf_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[j];

					hold_m_color.resize(c + 1);
					hold_m_color[c] = hold_color[j];

					c++;
				}

			}
			else if (hold_an[j] == 2) {
				for (int l = 0; k > l; l++) {
					hold_m_info.resize(c + 1);
					hold_m_info[c] = noteinfo[j][0] + ((double)60 / (double)240 / (double)interval) * ((double)l + (double)1);

					hold_m_leftpos.resize(c + 1);
					hold_m_leftpos[c] = -1 * (noteinfo[i][1] - noteinfo[j][1]) / pow(k, 2.0) * pow(k - l, 2.0) + noteinfo[i][1] - (double)8;

					hold_m_width.resize(c + 1);
					hold_m_width[c] = -1 * (noteinfo[i][2] - noteinfo[j][2]) / pow(k, 2.0) * pow(k - l, 2.0) + noteinfo[i][2];

					hold_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[j];

					holf_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[j];

					hold_m_color.resize(c + 1);
					hold_m_color[c] = hold_color[j];


					c++;
				}

			}
		}
		int repc = 0;
		while (rep) {

			if (repc == 0) {
				n = i;
			}
			else {
				i = n;
			}

			while (true) {
				n++;
				if (note <= n) {
					n--;
					break;
				}
				if (holdnum[j] == holdnum[n]) {
					if (notekinds[n] == 7 || notekinds[n] == 8) {
						if (hold_uf[n] == 1) {

							hold_color[n] = hold_color[j];
							uf_pos.resize(uf_c + 1);
							uf_pos[uf_c] = n;
							uf_num.resize(uf_c + 1);
							uf_num[uf_c] = holdnum[n];

							uf_c++;
						}
						else {

							break;
						}
					}
					if (notekinds[n] == 9) {
						rep = false;
						break;
					}
				}
			}

			hold_color[n] = hold_color[j];

			double hold_long = noteinfo[n][0] - noteinfo[i][0];

			int k = hold_long * 4 * interval;

			if (notekinds[n] == 9) {
				k -= 7;
			}
			else if (notekinds[n] == 7 || notekinds[n] == 8) {
				k += 1;
			}

			if (hold_an[i] == 0) {
				for (int l = 0; k > l; l++) {
					hold_m_info.resize(c + 1);
					hold_m_info[c] = noteinfo[i][0] + ((double)60 / (double)240 / (double)interval) * ((double)l + (double)1);

					hold_m_leftpos.resize(c + 1);
					hold_m_leftpos[c] = ((noteinfo[n][1] - noteinfo[i][1])) / (double)k * (double)l + (noteinfo[i][1] - (double)8);

					hold_m_width.resize(c + 1);
					hold_m_width[c] = ((noteinfo[n][2] - noteinfo[i][2])) / (double)k * (double)l + noteinfo[i][2];

					hold_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[i];

					hold_m_color.resize(c + 1);
					hold_m_color[c] = hold_color[j];

					c++;
				}
			}
			else if (hold_an[i] == 1) {
				for (int l = 0; k > l; l++) {
					hold_m_info.resize(c + 1);
					hold_m_info[c] = noteinfo[i][0] + ((double)60 / (double)240 / (double)interval) * ((double)l + (double)1);

					hold_m_leftpos.resize(c + 1);
					hold_m_leftpos[c] = (noteinfo[n][1] - noteinfo[i][1]) / pow(k, 2.0) * pow(l + 1, 2.0) + (noteinfo[i][1] - (double)8);

					hold_m_width.resize(c + 1);
					hold_m_width[c] = (noteinfo[n][2] - noteinfo[i][2]) / pow(k, 2.0) * pow(l + 1, 2.0) + noteinfo[i][2];

					hold_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[i];

					hold_m_color.resize(c + 1);
					hold_m_color[c] = hold_color[j];

					c++;
				}
			}
			else if (hold_an[i] == 2) {
				for (int l = 0; k > l; l++) {
					hold_m_info.resize(c + 1);
					hold_m_info[c] = noteinfo[i][0] + ((double)60 / (double)240 / (double)interval) * ((double)l + (double)1);

					hold_m_leftpos.resize(c + 1);
					hold_m_leftpos[c] = -1 * (noteinfo[n][1] - noteinfo[i][1]) / pow(k, 2.0) * pow(k - l, 2.0) + noteinfo[n][1] - (double)8;

					hold_m_width.resize(c + 1);
					hold_m_width[c] = -1 * (noteinfo[n][2] - noteinfo[i][2]) / pow(k, 2.0) * pow(k - l, 2.0) + noteinfo[n][2];

					hold_m_num.resize(c + 1);
					hold_m_num[c] = holdnum[i];

					hold_m_color.resize(c + 1);
					hold_m_color[c] = hold_color[j];

					c++;
				}

			}


			repc++;
		}
	}

	//有形中継点の位置を変える
	for (int i = 0, j = 0; hold_m_info.size() > i && uf_num.size() > j; i++) {
		if (fabs(noteinfo[uf_pos[j]][0] - hold_m_info[i]) <= 0.001 && holdnum[uf_pos[j]] == uf_num[j]) {
			noteinfo[uf_pos[j]][1] = hold_m_leftpos[i] + (double)8;
			noteinfo[uf_pos[j]][2] = hold_m_width[i];
			j++;
		}
	}

	//表示しないノーツを消す
	for (int i = 0; note > i; i++) {
		if (notekinds[i] == 15) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 9) {
						notekinds[j] = hold_color[j] * 7 + 3;
						notekinds[i] = 0;
					}
				}
			}
		}
		if (notekinds[i] == 16) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 9) {
						notekinds[j] = hold_color[j] * 7 + 4;
						notekinds[i] = 0;
					}
				}
			}
		}
		if (notekinds[i] == 17) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 9) {
						notekinds[j] = hold_color[j] * 7 + 5;

						notekinds[i] = 0;
					}
				}
			}
		}
		if (notekinds[i] == 10 || notekinds[i] == 11 || notekinds[i] == 12) {
			for (int j = 0; note > j; j++) {
				if (j != i) {
					if (noteinfo[i][0] == noteinfo[j][0] && noteinfo[i][1] == noteinfo[j][1] && noteinfo[i][2] == noteinfo[j][2] && notekinds[j] == 9) {

						notekinds[j] = 0;
					}
				}
			}
		}
	}

	//ノーツ情報の並び替え
	int num = 0;
	for (int r = 0; hold_m_info.size() > r; r++) {
		for (int s = r + 1; hold_m_info.size() > s; s++) {
			if (hold_m_info[r] > hold_m_info[s]) {

				tmp = hold_m_info[r];
				hold_m_info[r] = hold_m_info[s];
				hold_m_info[s] = tmp;

				tmp = hold_m_leftpos[r];
				hold_m_leftpos[r] = hold_m_leftpos[s];
				hold_m_leftpos[s] = tmp;

				tmp = hold_m_width[r];
				hold_m_width[r] = hold_m_width[s];
				hold_m_width[s] = tmp;

				num = hold_m_num[r];
				hold_m_num[r] = hold_m_num[s];
				hold_m_num[s] = num;

				num = hold_m_color[r];
				hold_m_color[r] = hold_m_color[s];
				hold_m_color[s] = num;
			}
		}
	}

	//ノーツ情報の並び替え
	for (int r = 0; note > r; r++) {
		for (int s = r + 1; note > s; s++) {
			if (noteinfo[r][0] > noteinfo[s][0]) {

				tmp = noteinfo[r][0];
				noteinfo[r][0] = noteinfo[s][0];
				noteinfo[s][0] = tmp;

				tmp = noteinfo[r][1];
				noteinfo[r][1] = noteinfo[s][1];
				noteinfo[s][1] = tmp;

				tmp = noteinfo[r][2];
				noteinfo[r][2] = noteinfo[s][2];
				noteinfo[s][2] = tmp;

				tmp2 = notekinds[r];
				notekinds[r] = notekinds[s];
				notekinds[s] = tmp2;

				tmp2 = holdnum[r];
				holdnum[r] = holdnum[s];
				holdnum[s] = tmp2;

				tmp2 = hold_an[r];
				hold_an[r] = hold_an[s];
				hold_an[s] = tmp2;

				tmp2 = hold_color[r];
				hold_color[r] = hold_color[s];
				hold_color[s] = tmp2;
			}
		}
	}


	hold_m_m.resize(hold_m_info.size());
	hold_m_f.resize(hold_m_info.size());
	hold_m_y.resize(hold_m_info.size());
	hold_s_f.resize(hold_m_info.size());

	for (int i = 0; hold_m_info.size() > i; i++) {
		hold_m_f[i] = false;
		hold_s_f[i] = false;
	}

	std::vector<bool> effect_f;
	std::vector<int> effect_k;
	effect_f.resize(note + 1);
	effect_k.resize(note + 1);
	for (int i = 0; note + 1 > i; i++) {
		effect_f[i] = false;
		effect_k[i] = 0;
	}


	SetFontSize(40);
	int StrLen = strlen(musicname[f % music_total].c_str());
	int StrWidth = GetDrawStringWidth(musicname[f % music_total].c_str(), StrLen);
	int musicFont = CreateFontToHandle("FOT-ロダンNTLG Pro DB", 40, -1, DX_FONTTYPE_ANTIALIASING_8X8);
	SetFontSize(20);
	std::string mstr = "作詞：ー　作曲：ー　編曲：ー";
	int StrLen2 = strlen(mstr.c_str());
	int StrWidth2 = GetDrawStringWidth(mstr.c_str(), StrLen2);
	int musicFont2 = CreateFontToHandle("FOT-ロダンNTLG Pro DB", 20, -1, DX_FONTTYPE_ANTIALIASING_8X8);
	std::string mstr2 = "歌：ー";
	int StrLen3 = strlen(mstr2.c_str());
	int StrWidth3 = GetDrawStringWidth(mstr2.c_str(), StrLen3);
	int white = GetColor(255, 255, 255);

	int now_t, start_t = GetNowCount();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		now_t = GetNowCount() - start_t;

		if (now_t < 4000) {
			if (CheckSoundMem(start) == 0) {
				PlaySoundMem(start, DX_PLAYTYPE_BACK);
			}
			int thick = 255 * now_t / 800;
			DrawExtendGraph(0, 0, 1281, 721, now_loading, true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
			DrawBox(0, 0, 1281, 721, white, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (4000 < now_t && now_t < 9500) {
			DrawModiGraph(466, 30, 815, 30, 808, 364, 473, 364, jacket, true);
			DrawModiGraph(220, 195, 390, 185, 395, 295, 225, 305, jacketL, true);
			DrawModiGraph(921, 72, 1095, 78, 1089, 190, 919, 181, jacketR, true);
			DrawGraph(0, 0, back, true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
			DrawModiGraph(808, 758, 473, 758, 466, 424, 815, 424, jacket, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			if (8500 < now_t) {
				int thick = (now_t - 8500) * -255 / 500 + 255;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
			}

			int light_x = -1 * ((now_t - 4000) % 2000) * 920 / 2000 + 720;
			DrawExtendGraph(0, light_x, 1281, 200 + light_x, light, true);

			for (int i = 0; 22 > i; i++) {
				for (int j = 0; 12 > j; j++) {
					DrawRotaGraph(30 + 60 * i, 30 + 60 * j, 0.6489f, 0, bg_bk, true);
				}
			}
			DrawRotaGraph(640, 260, 0.35, 175 * M_PI / 180, jacket_back, true);
			DrawRotaGraph(640, 260, 378 / (double)imS, 0, jacket, true);
			DrawRotaGraph(640, 485, 0.7, 0, text_master, true);

			DrawStringToHandle(640 - StrWidth / 2, 530, musicname[f % music_total].c_str(), white, musicFont);

			DrawStringToHandle(640 - StrWidth2 / 2, 590, mstr.c_str(), white, musicFont2);

			DrawStringToHandle(640 - StrWidth3 / 2, 630, mstr2.c_str(), white, musicFont2);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			if (now_t < 5000) {
				int thick = -255 * now_t / 1000 + 1275;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
				DrawBox(0, 0, 1281, 721, white, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
		else if (9500 < now_t && now_t < 11500) {
			DrawModiGraph(466, 30, 815, 30, 808, 364, 473, 364, jacket, true);
			DrawModiGraph(220, 195, 390, 185, 395, 295, 225, 305, jacketL, true);
			DrawModiGraph(921, 72, 1095, 78, 1089, 190, 919, 181, jacketR, true);
			DrawGraph(0, 0, back, true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
			DrawModiGraph(808, 758, 473, 758, 466, 424, 815, 424, jacket, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			int thick = (now_t - 9500) * 255 / 2000;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
			DrawGraph(0, 0, line, true);
			DrawExtendGraph(0, 0, 515, 97, gauge, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (11500 < now_t) {
			break;
		}

	}

	SetFontSize(16);

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	ClearDrawScreen();
	DrawModiGraph(466, 30, 815, 30, 808, 364, 473, 364, jacket, true);
	DrawModiGraph(220, 195, 390, 185, 395, 295, 225, 305, jacketL, true);
	DrawModiGraph(921, 72, 1095, 78, 1089, 190, 919, 181, jacketR, true);
	DrawGraph(0, 0, back, true); //画像の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
	DrawModiGraph(808, 758, 473, 758, 466, 424, 815, 424, jacket, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, line, true);
	DrawExtendGraph(0, 0, 515, 515 * 146 / 776, gauge, true);

	SetDrawScreen(DX_SCREEN_BACK);	//作画場所変更


	int u = 0, judgeT = 0, log[16], arrow_size, arrowTime, ar, thick, thick2, thick3;
	float judgeF = 0.f, comboF = 0.f;
	bool mu = true, loop[5], lm[2] = { false, false };
	for (int i = 0; 5 > i; i++) { loop[i] = true; }
	counter = 0;
	double hLLine, hRLine, mm, mmm;
	std::vector<int> f_ar;

	int counter2 = 0, counter3 = 0, counter4 = 0, counter5 = 0, counter6 = 0, counter7 = 0, counter8 = 0, ct = 0, ct2 = 0, long_ef[16];
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//時間関係
		if (start_time == 0) {
			start_time = GetNowHiPerformanceCount();
		}
		now_time = GetNowHiPerformanceCount();
		currentTime = (int)((now_time - start_time) / 1000); // 単位[ms]

		arrowTime = currentTime % 500;

		if (currentTime >= 1000 + offset && mu) {						//音楽再生
			PlaySoundMem(music, DX_PLAYTYPE_BACK);
			mu = false;
		}

		//ノーツ生成
		if (currentTime >= 1000 * 60 / 240 * counter / interval && loop[0]) {
			while (noteinfo[counter][0] * 1000 <= currentTime) {
				note_f[counter] = true;
				note_y[counter] = 0.f;
				note_m[counter] = 0.08;

				if (note > counter + 1) {
					counter++;
				}
				else {
					loop[0] = false;
					break;
				}
			}

		}

		for (int i = 0; 16 > i; i++) { log[i] = -1; }
		if (hold_m_info.size() != 0) {
			while (hold_m_info[counter2] * 1000 <= currentTime) {
				hold_m_f[counter2] = true;
				hold_m_y[counter2] = 3.82f;

				if (hold_m_info.size() > counter2 + 1) {
					counter2++;
				}
				else {
					loop[1] = false;
					break;
				}
			}
			while (hold_m_info[counter3] * 1000 + 1000 <= currentTime) {

				if (hold_m_info.size() > counter3 + 1) {
					log[hold_m_num[counter3]] = counter3;
					counter3++;
				}
				else {
					loop[2] = false;
					break;
				}
			}
		}

		DrawModiGraph(466, 30, 815, 30, 808, 364, 473, 364, jacket, true);
		DrawModiGraph(220, 195, 390, 185, 395, 295, 225, 305, jacketL, true);
		DrawModiGraph(921, 72, 1095, 78, 1089, 190, 919, 181, jacketR, true);
		DrawGraph(0, 0, back, true); //判定ラインその他もろもろ作画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
		DrawModiGraph(808, 758, 473, 758, 466, 424, 815, 424, jacket, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(0, 0, line, true);
		DrawExtendGraph(0, 0, 515, 515 * 146 / 776, gauge, true);
		if (combo != 0) {
			DrawRotaGraph(1096, 255, 0.63, 0, combotxt, true);
		}

		lm[0] = true; lm[1] = true;
		for (int i = 0; 16 > i; i++) { long_ef[i] = 0; SetDrawScreen(hold_m_sc[i]); ClearDrawScreen(); }
		SetDrawScreen(DX_SCREEN_BACK);

		//ノーツ作画
		for (int j = counter4; counter2 > j; j++) {
			if (hold_m_f[j]) {

				hold_m_m[j] = pow(((double)currentTime - hold_m_info[j] * 1000), 2.0) * 23 / 25000000 + 0.08;
				hold_m_y[j] = pow(((float)currentTime - (float)hold_m_info[j] * 1000), 2.0) * 3 / 6250;

				if (hold_m_y[j] > 480) {
					hold_m_f[j] = false;
					long_ef[hold_m_num[j]] = j;
					counter4++;
					lm[hold_m_color[j]] = false;
				}

				double hLLine, hRLine;

				hLLine = hold_m_leftpos[j];
				hRLine = hLLine + hold_m_width[j];

				double hx1 = 640 + 80 * hold_m_m[j] * hLLine - 5 * hold_m_m[j] * 5 * hLLine / 36 / 2 + 10 * hold_m_m[j];
				double hx2 = 640 + 80 * hold_m_m[j] * hRLine - 5 * hold_m_m[j] * 5 * hRLine / 36 / 2 - 10 * hold_m_m[j];
				double hx3 = 640 + 80 * hold_m_m[j] * hRLine + 5 * hold_m_m[j] * 5 * hRLine / 36 / 2 - 10 * hold_m_m[j];
				double hx4 = 640 + 80 * hold_m_m[j] * hLLine + 5 * hold_m_m[j] * 5 * hLLine / 36 / 2 + 10 * hold_m_m[j];

				if (hold_m_color[j] == 0) {
					SetDrawScreen(hold_m_sc[hold_m_num[j]]);
					DrawModiGraph(hx1, hold_m_y[j] + 50 * hold_m_m[j], hx2, hold_m_y[j] + 50 * hold_m_m[j], hx3, hold_m_y[j] + 55 * hold_m_m[j], hx4, hold_m_y[j] + 55 * hold_m_m[j], Lnote_m, true);
					SetDrawScreen(DX_SCREEN_BACK);
				}
				else if (hold_m_color[j] == 1) {
					SetDrawScreen(hold_m_sc[hold_m_num[j]]);
					DrawModiGraph(hx1, hold_m_y[j] + 50 * hold_m_m[j], hx2, hold_m_y[j] + 50 * hold_m_m[j], hx3, hold_m_y[j] + 55 * hold_m_m[j], hx4, hold_m_y[j] + 55 * hold_m_m[j], CLnote_m, true);
					SetDrawScreen(DX_SCREEN_BACK);
				}
			}
		}

		for (int i = 0; 16 > i; i++) {
			if (log[i] != -1) {
				int j = log[i];

				hLLine = hold_m_leftpos[j];
				hRLine = hLLine + hold_m_width[j];

				double lx1 = 640 + 80 * hLLine - 545 * hLLine / 36 / 2 - 30;
				double lx2 = 640 + 80 * (hLLine + 2) - 545 * (hLLine + 2) / 36 / 2 + 30;
				double lx3 = 640 + 80 * (hLLine + 2) + 545 * (hLLine + 2) / 36 / 2 + 30;
				double lx4 = 640 + 80 * hLLine + 545 * hLLine / 36 / 2 - 30;

				double rx1 = 640 + 80 * (hRLine - 2) - 545 * (hRLine - 2) / 36 / 2 - 30;
				double rx2 = 640 + 80 * hRLine - 545 * hRLine / 36 / 2 + 30;
				double rx3 = 640 + 80 * hRLine + 545 * hRLine / 36 / 2 + 30;
				double rx4 = 640 + 80 * (hRLine - 2) + 545 * (hRLine - 2) / 36 / 2 - 30;


				if (hold_m_color[j] == 0) {
					DrawModiGraph(lx1, 480, lx2, 480, lx3, 589, lx4, 589, Lnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67, 480, rx2 - 67, 480, rx3 - 75, 589, lx4 + 75, 589, Lnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, 480, rx2, 480, rx3, 589, rx4, 589, Lnote_r, true);	//右ノーツ作画
				}
				else if (hold_m_color[j] == 1) {
					DrawModiGraph(lx1, 480, lx2, 480, lx3, 589, lx4, 589, Cnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67, 480, rx2 - 67, 480, rx3 - 75, 589, lx4 + 75, 589, Cnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, 480, rx2, 480, rx3, 589, rx4, 589, Cnote_r, true);	//右ノーツ作画
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
			DrawGraph(0, 0, hold_m_sc[i], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		if (lm[0]) {
			StopSoundMem(long_sound);
		}
		if (lm[1]) {
			StopSoundMem(c_long_sound);
		}
		ar = 0; f_ar.resize(0);
		for (int j = counter5; counter + 1 > j; j++) {
			if (note_f[j]) {

				note_m[j] = ((double)currentTime - noteinfo[j][0] * 1000) * ((double)currentTime - noteinfo[j][0] * 1000) * 23 / 25000000 + 0.08;
				note_y[j] = ((float)currentTime - (float)noteinfo[j][0] * 1000) * ((float)currentTime - (float)noteinfo[j][0] * 1000) * 3 / 6250;

				if (note_y[j] > 470) {

					note_f[j] = false;	//判定ラインを過ぎたらfalse

					counter5++;
					counter6++;

					if (notekinds[j] == 1) {
						effect_f[j] = true;
						effect_k[j] = 1;
						PlaySoundMem(normal_notes_sound, DX_PLAYTYPE_BACK);
					}
					else if (notekinds[j] == 2) {
						effect_f[j] = true;
						effect_k[j] = 2;
						PlaySoundMem(critical_notes_sound, DX_PLAYTYPE_BACK);
					}
					else if (notekinds[j] == 3 || notekinds[j] == 4 || notekinds[j] == 5) {
						effect_f[j] = true;
						effect_k[j] = 3;
						PlaySoundMem(normal_flick_sound, DX_PLAYTYPE_BACK);
					}
					else if (notekinds[j] == 6) {
						if (hold_color[j] == 0) {
							effect_f[j] = true;
							effect_k[j] = 4;
							PlaySoundMem(normal_notes_sound, DX_PLAYTYPE_BACK);
							if (CheckSoundMem(long_sound) == 0) {
								PlaySoundMem(long_sound, DX_PLAYTYPE_LOOP);
							}
						}
						else if (hold_color[j] == 1) {
							effect_f[j] = true;
							effect_k[j] = 2;
							PlaySoundMem(critical_notes_sound, DX_PLAYTYPE_BACK);
							if (CheckSoundMem(c_long_sound) == 0) {
								PlaySoundMem(c_long_sound, DX_PLAYTYPE_LOOP);
							}
						}
					}
					else if (notekinds[j] == 9) {
						if (hold_color[j] == 0) {
							effect_f[j] = true;
							effect_k[j] = 4;
							PlaySoundMem(normal_notes_sound, DX_PLAYTYPE_BACK);
						}
						else if (hold_color[j] == 1) {
							effect_f[j] = true;
							effect_k[j] = 2;
							PlaySoundMem(critical_notes_sound, DX_PLAYTYPE_BACK);
						}
					}
					else if (notekinds[j] == 7) {
						PlaySoundMem(long_among_sound, DX_PLAYTYPE_BACK);
					}
					else if (notekinds[j] == 10 || notekinds[j] == 11 || notekinds[j] == 12) {
						effect_f[j] = true;
						effect_k[j] = 2;
						PlaySoundMem(critical_flick_sound, DX_PLAYTYPE_BACK);
					}

					if (notekinds[j] != 8 && notekinds[j] != 0) {
						judgeF = 0.45f;
						judgeT = currentTime;
						comboF = 0.775f;
						combo++;
					}
				}
				LLine = noteinfo[j][1] - (double)8, RLine = noteinfo[j][1] + noteinfo[j][2] - (double)8;

				double lx1 = 640 + 80 * note_m[j] * LLine - 109 * note_m[j] * 5 * LLine / 36 / 2 - 30 * note_m[j];
				double lx2 = 640 + 80 * note_m[j] * (LLine + 2) - 109 * note_m[j] * 5 * (LLine + 2) / 36 / 2 + 30 * note_m[j];
				double lx3 = 640 + 80 * note_m[j] * (LLine + 2) + 109 * note_m[j] * 5 * (LLine + 2) / 36 / 2 + 30 * note_m[j];
				double lx4 = 640 + 80 * note_m[j] * LLine + 109 * note_m[j] * 5 * LLine / 36 / 2 - 30 * note_m[j];

				double rx1 = 640 + 80 * note_m[j] * (RLine - 2) - 109 * note_m[j] * 5 * (RLine - 2) / 36 / 2 - 30 * note_m[j];
				double rx2 = 640 + 80 * note_m[j] * RLine - 109 * note_m[j] * 5 * RLine / 36 / 2 + 30 * note_m[j];
				double rx3 = 640 + 80 * note_m[j] * RLine + 109 * note_m[j] * 5 * RLine / 36 / 2 + 30 * note_m[j];
				double rx4 = 640 + 80 * note_m[j] * (RLine - 2) + 109 * note_m[j] * 5 * (RLine - 2) / 36 / 2 - 30 * note_m[j];

				if (notekinds[j] == 1) {			//通常ノーツ
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Nnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Nnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Nnote_r, true);	//右ノーツ作画
				}
				else if (notekinds[j] == 2) {		//クリティカルノーツ
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Cnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Cnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Cnote_r, true);	//右ノーツ作画
				}
				else if (notekinds[j] == 3) {		//上フリック
					ar++;
					f_ar.resize(ar);
					f_ar[ar - 1] = j;
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Fnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Fnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Fnote_r, true);	//右ノーツ作画
				}
				else if (notekinds[j] == 4) {		//左フリック
					ar++;
					f_ar.resize(ar);
					f_ar[ar - 1] = j;
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Fnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Fnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Fnote_r, true);	//右ノーツ作画
				}
				else if (notekinds[j] == 5) {		//右フリック
					ar++;
					f_ar.resize(ar);
					f_ar[ar - 1] = j;
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Fnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Fnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Fnote_r, true);	//右ノーツ作画
				}
				else if (notekinds[j] == 6) {		//長押し始点
					if (hold_color[j] == 0) {
						DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Lnote_l, true);	//左ノーツ作画
						DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Lnote_c, true);	//中ノーツ作画
						DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Lnote_r, true);	//右ノーツ作画
					}
					else if (hold_color[j] == 1) {
						DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Cnote_l, true);	//左ノーツ作画
						DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Cnote_c, true);	//中ノーツ作画
						DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Cnote_r, true);	//右ノーツ作画
					}
				}
				else if (notekinds[j] == 7) {		//有形中継点
					if (hold_color[j] == 0) {
						DrawRotaGraph((lx1 + rx2) / 2, note_y[j] + 54.5 * note_m[j], note_m[j], 0, Lnote_a, true);
					}
					else if (hold_color[j] == 1) {
						DrawRotaGraph((lx1 + rx2) / 2, note_y[j] + 54.5 * note_m[j], note_m[j], 0, CLnote_a, true);
					}
				}
				else if (notekinds[j] == 8) {		//無形中継点

				}
				else if (notekinds[j] == 9) {		//長押し終点
					if (hold_color[j] == 0) {
						DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Lnote_l, true);	//左ノーツ作画
						DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Lnote_c, true);	//中ノーツ作画
						DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Lnote_r, true);	//右ノーツ作画
					}
					else if (hold_color[j] == 1) {
						DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Cnote_l, true);	//左ノーツ作画
						DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Cnote_c, true);	//中ノーツ作画
						DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Cnote_r, true);	//右ノーツ作画
					}
				}
				else if (notekinds[j] == 10) {		//黄上フリック
					ar++;
					f_ar.resize(ar);
					f_ar[ar - 1] = j;
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Cnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Cnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Cnote_r, true);	//右ノーツ作画
				}
				else if (notekinds[j] == 11) {		//黄左フリック
					ar++;
					f_ar.resize(ar);
					f_ar[ar - 1] = j;
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Cnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Cnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Cnote_r, true);	//右ノーツ作画
				}
				else if (notekinds[j] == 12) {		//黄右フリック
					ar++;
					f_ar.resize(ar);
					f_ar[ar - 1] = j;
					DrawModiGraph(lx1, note_y[j], lx2, note_y[j], lx3, note_y[j] + 109 * note_m[j], lx4, note_y[j] + 109 * note_m[j], Cnote_l, true);	//左ノーツ作画
					DrawModiGraph(lx1 + 67 * note_m[j], note_y[j], rx2 - 67 * note_m[j], note_y[j], rx3 - 75 * note_m[j], note_y[j] + 109 * note_m[j], lx4 + 75 * note_m[j], note_y[j] + 109 * note_m[j], Cnote_c, true);	//中ノーツ作画
					DrawModiGraph(rx1, note_y[j], rx2, note_y[j], rx3, note_y[j] + 109 * note_m[j], rx4, note_y[j] + 109 * note_m[j], Cnote_r, true);	//右ノーツ作画
				}
			}
		}

		if (arrowTime >= 300) {
			thick = -51 / 40 * arrowTime + 637.5;
		}
		else {
			thick = 255;
		}

		for (int i = 0; f_ar.size() > i; i++) {			//フリック矢印作画
			int j = f_ar[i];
			LLine = noteinfo[j][1] - (double)8, RLine = noteinfo[j][1] + noteinfo[j][2] - (double)8;
			if (RLine - LLine < 7) { arrow_size = (int)(RLine - LLine) - 1; }
			else { arrow_size = 5; }

			if (notekinds[j] == 3) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
				DrawRotaGraph(640 + (RLine + LLine) / 2 * 80 * note_m[j], note_y[j] - (arrowTime / 5 + 20) * note_m[j], 0.7 * note_m[j], 0, Fnote_ar[arrow_size][0], true, false);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (notekinds[j] == 4) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
				DrawRotaGraph(640 + (RLine + LLine) / 2 * 80 * note_m[j] - arrowTime / 10 * note_m[j], note_y[j] - (86.6 * arrowTime / 500 + 20) * note_m[j], 0.7 * note_m[j], 0, Fnote_ar[arrow_size][1], true, false);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (notekinds[j] == 5) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
				DrawRotaGraph(640 + (RLine + LLine) / 2 * 80 * note_m[j] + arrowTime / 10 * note_m[j], note_y[j] - (86.6 * arrowTime / 500 + 20) * note_m[j], 0.7 * note_m[j], 0, Fnote_ar[arrow_size][1], true, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (notekinds[j] == 10) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
				DrawRotaGraph(640 + (RLine + LLine) / 2 * 80 * note_m[j], note_y[j] - (arrowTime / 5 + 20) * note_m[j], 0.7 * note_m[j], 0, CFnote_ar[arrow_size][0], true, false);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (notekinds[j] == 11) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
				DrawRotaGraph(640 + (RLine + LLine) / 2 * 80 * note_m[j] - arrowTime / 10 * note_m[j], note_y[j] - (86.6 * arrowTime / 500 + 20) * note_m[j], 0.7 * note_m[j], 0, CFnote_ar[arrow_size][1], true, false);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (notekinds[j] == 12) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
				DrawRotaGraph(640 + (RLine + LLine) / 2 * 80 * note_m[j] + arrowTime / 10 * note_m[j], note_y[j] - (86.6 * arrowTime / 500 + 20) * note_m[j], 0.7 * note_m[j], 0, CFnote_ar[arrow_size][1], true, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
		for (int i = 0; 16 > i; i++) {
			if (long_ef[i] != 0) {
				int j = long_ef[i];
				double hLLine, hRLine;

				LLine = hold_m_leftpos[j];
				RLine = LLine + hold_m_width[j];

				double height = 313;

				double ef_x1 = 640 + 80 * LLine + height / 17 * LLine;
				double ef_x2 = 640 + 80 * RLine + height / 17 * RLine;
				double ef_x3 = 640 + 80 * RLine;
				double ef_x4 = 640 + 80 * LLine;

				double fx1 = 640.0 + (LLine + RLine) * 80 / 2 - 200 - (LLine / 2 + RLine / 2 - 2.5) * 70 * 5 / 36;
				double fx2 = 640.0 + (LLine + RLine) * 80 / 2 + 200 - (LLine / 2 + RLine / 2 + 2.5) * 70 * 5 / 36;
				double fx3 = 640.0 + (LLine + RLine) * 80 / 2 + 200 + (LLine / 2 + RLine / 2 + 2.5) * 70 * 5 / 36;
				double fx4 = 640.0 + (LLine + RLine) * 80 / 2 - 200 + (LLine / 2 + RLine / 2 - 2.5) * 70 * 5 / 36;

				if (hold_m_color[j] == 0) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					DrawModiGraph(ef_x1, 530 - height, ef_x2, 530 - height, ef_x3, 530, ef_x4, 530, long_effect, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					DrawModiGraph(fx1, 530 - 140, fx2, 520 - 140, fx3, 520 + 140, fx4, 520 + 140, long_effect2, true);
				}
				if (hold_m_color[j] == 1) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					DrawModiGraph(ef_x1, 530 - height, ef_x2, 530 - height, ef_x3, 530, ef_x4, 530, critical_effect, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					DrawModiGraph(fx1, 530 - 140, fx2, 520 - 140, fx3, 520 + 140, fx4, 520 + 140, critical_effect2, true);
				}
			}
		}

		if (note > i) {
			for (int i = counter7; counter6 + 1 > i; i++) {
				if (currentTime - (noteinfo[i][0] * 1000 + 1000) <= 250) {

					LLine = noteinfo[i][1] - (double)8, RLine = noteinfo[i][1] + noteinfo[i][2] - (double)8;

					double height, width_m;

					if (currentTime - (noteinfo[i][0] * 1000 + 1000) <= 100) {
						height = 313 * (currentTime - (noteinfo[i][0] * 1000 + 1000)) / 100;
						thick = 255;
					}
					else if (currentTime - (noteinfo[i][0] * 1000 + 1000) > 100) {
						height = 313;
						thick = -17 * (currentTime - (noteinfo[i][0] * 1000 + 1000)) / 10 + 1275 / 3;
					}

					if (currentTime - (noteinfo[i][0] * 1000 + 1000) <= 250 / 3) {
						thick2 = 3.06 * (currentTime - (noteinfo[i][0] * 1000 + 1000));
					}
					else if (currentTime - (noteinfo[i][0] * 1000 + 1000) >= 250 / 3 && currentTime - (noteinfo[i][0] * 1000 + 1000) <= 500 / 3) {
						thick2 = 255;
					}
					else if (currentTime - (noteinfo[i][0] * 1000 + 1000) >= 500 / 3) {
						thick2 = -3.06 * (currentTime - (noteinfo[i][0] * 1000 + 1000)) + 765;
					}
					width_m = -0.024 * (currentTime - (noteinfo[i][0] * 1000 + 1000)) + 4.5;

					if (currentTime - (noteinfo[i][0] * 1000 + 1000) <= 400) {
						mm = 0.1 * pow((currentTime - (noteinfo[i][0] * 1000 + 1000)), 0.5);
						mmm = 0.25 * pow((currentTime - (noteinfo[i][0] * 1000 + 1000)), 0.5);
						thick3 = -0.00159375 * pow((currentTime - (noteinfo[i][0] * 1000 + 1000)), 2.0) + 255;
					}

					double ef_x1 = 640 + 80 * LLine + height / 17 * LLine;
					double ef_x2 = 640 + 80 * RLine + height / 17 * RLine;
					double ef_x3 = 640 + 80 * RLine;
					double ef_x4 = 640 + 80 * LLine;
					if (effect_k[i] == 1) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
						DrawModiGraph(ef_x1, 530 - height, ef_x2, 530 - height, ef_x3, 530, ef_x4, 530, tap_effect, true);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}
					else if (effect_k[i] == 2) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
						DrawModiGraph(ef_x1, 530 - height, ef_x2, 530 - height, ef_x3, 530, ef_x4, 530, critical_effect, true);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}
					else if (effect_k[i] == 3) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
						DrawModiGraph(ef_x1, 530 - height, ef_x2, 530 - height, ef_x3, 530, ef_x4, 530, flick_effect, true);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}
					else if (effect_k[i] == 4) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick);
						DrawModiGraph(ef_x1, 530 - height, ef_x2, 530 - height, ef_x3, 530, ef_x4, 530, long_effect, true);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}

					double fx1 = 640.0 + (LLine + RLine) * 80 / 2 - 120 * mm - (LLine / 2 + RLine / 2 - 1.25) * 70 * 5 * mm / 36;
					double fx2 = 640.0 + (LLine + RLine) * 80 / 2 + 120 * mm - (LLine / 2 + RLine / 2 + 1.25) * 70 * 5 * mm / 36;
					double fx3 = 640.0 + (LLine + RLine) * 80 / 2 + 120 * mm + (LLine / 2 + RLine / 2 + 1.25) * 70 * 5 * mm / 36;
					double fx4 = 640.0 + (LLine + RLine) * 80 / 2 - 120 * mm + (LLine / 2 + RLine / 2 - 1.25) * 70 * 5 * mm / 36;

					if (notekinds[i] == 1) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, tap_effect2, true);
					}
					else if (notekinds[i] == 2) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, critical_effect2, true);
					}
					else if (notekinds[i] == 3) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick2);
						DrawRotaGraph3(640 + (LLine + RLine) * 80 / 2, 510, 64, 214, width_m, 1.8, (LLine + RLine) * 3 / 2 * M_PI / 180, flick_effect2, true, false);

						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, flick_effect3, true);
					}
					else if (notekinds[i] == 4) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick2);
						DrawRotaGraph3(640 + (LLine + RLine) * 80 / 2, 510, 64, 214, width_m, 1.8, (-30 + (LLine + RLine) * 3 / 2) * M_PI / 180, flick_effect2, true, false);

						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, flick_effect3, true);
					}
					else if (notekinds[i] == 5) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick2);
						DrawRotaGraph3(640 + (LLine + RLine) * 80 / 2, 510, 64, 214, width_m, 1.8, (30 + (LLine + RLine) * 3 / 2) * M_PI / 180, flick_effect2, true, false);

						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, flick_effect3, true);
					}
					else if (notekinds[i] == 6) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, long_effect2, true);
					}
					else if (notekinds[i] == 7) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawRotaGraph(640 + (LLine + RLine) * 80 / 2, 528, mmm, M_PI / 4, long_effect3, true);
					}
					else if (notekinds[i] == 9) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, long_effect2, true);
					}
					else if (notekinds[i] == 10) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick2);
						DrawRotaGraph3(640 + (LLine + RLine) * 80 / 2, 510, 64, 214, width_m, 1.8, (LLine + RLine) * 3 / 2 * M_PI / 180, cflick_effect2, true, false);

						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, critical_effect2, true);
					}
					else if (notekinds[i] == 11) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick2);
						DrawRotaGraph3(640 + (LLine + RLine) * 80 / 2, 510, 64, 214, width_m, 1.8, (-30 + (LLine + RLine) * 3 / 2) * M_PI / 180, cflick_effect2, true, false);

						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, critical_effect2, true);
					}
					else if (notekinds[i] == 12) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick2);
						DrawRotaGraph3(640 + (LLine + RLine) * 80 / 2, 510, 64, 214, width_m, 1.8, (30 + (LLine + RLine) * 3 / 2) * M_PI / 180, cflick_effect2, true, false);

						SetDrawBlendMode(DX_BLENDMODE_ALPHA, thick3);
						DrawModiGraph(fx1, 530 - 70 * mm, fx2, 520 - 70 * mm, fx3, 520 + 70 * mm, fx4, 520 + 70 * mm, critical_effect2, true);
					}
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else if (currentTime - (noteinfo[i][0] * 1000 + 1000) > 400) {
					effect_f[i] = false;
					counter7++;
				}
				if (note <= i + 1) {
					counter6 -= 1;
					break;
				}

			}
		}



		if (currentTime - judgeT > 0) {								//判定表示系
			judgeF = (currentTime - judgeT) * 0.01 + 0.45;
		}

		if (currentTime - judgeT >= 20) {
			judgeF = 0.65f;
		}

		if (currentTime - judgeT >= 250) {
			judgeF = 0.f;
		}
		if (judgeT == 0) {
			judgeF = 0.f;
		}

		DrawRotaGraph(640, 372, judgeF, 0, perfect, true);


		int buf1, buf2, buf3, buf4;
		if (combo == 0) {

		}
		else if (combo < 10) {
			DrawRotaGraph(1096, 315, comboF, 0, combonum[combo], true);
		}
		else if (combo >= 10 && combo < 100) {
			buf1 = combo % 10;
			buf2 = (combo - buf1) / 10;

			DrawRotaGraph(1056, 315, comboF, 0, combonum[buf2], true);
			DrawRotaGraph(1136, 315, comboF, 0, combonum[buf1], true);
		}
		else if (combo >= 100 && combo < 1000) {
			buf1 = combo % 100 % 10;
			buf2 = (combo % 100 - buf1) / 10;
			buf3 = (combo - 10 * buf2 - buf1) / 100;

			DrawRotaGraph(1016, 315, comboF, 0, combonum[buf3], true);
			DrawRotaGraph(1096, 315, comboF, 0, combonum[buf2], true);
			DrawRotaGraph(1176, 315, comboF, 0, combonum[buf1], true);
		}
		else if (combo >= 1000 && combo < 10000) {
			buf1 = combo % 1000 % 100 % 10;
			buf2 = (combo % 1000 % 100 - buf1) / 10;
			buf3 = (combo % 1000 - buf2 * 10 - buf1) / 100;
			buf4 = (combo - buf3 * 100 - buf2 * 10 - buf1) / 1000;

			DrawRotaGraph(976, 315, comboF, 0, combonum[buf4], true);
			DrawRotaGraph(1056, 315, comboF, 0, combonum[buf3], true);
			DrawRotaGraph(1136, 315, comboF, 0, combonum[buf2], true);
			DrawRotaGraph(1216, 315, comboF, 0, combonum[buf1], true);
		}

	}


	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}