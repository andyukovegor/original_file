#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "Graph.h" //êëàññ âåðøèí
#include "Link.h" //êëàññ ð¸áåð

using namespace sf;
using namespace std;



bool MouseOnNode(CircleShape &param,RenderWindow &window) { //ôóíêöèÿ îòñëåæèâàíèÿ íàæàòèÿ íà óçåë ãðàôà
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	if ((mouseX > param.getPosition().x && mouseY > param.getPosition().y) && (mouseX < (param.getPosition().x + param.getGlobalBounds().width)) && (mouseY < (param.getPosition().y + param.getGlobalBounds().height))) {
		return true;
	} else {
		return false;
	}
}



int MAX(int k,int s,int *H,int *T,int*F,int M) { // ôóíêöèÿ îïðåäåëåíèÿ ìàêñèìàëüíîãî ïîòîêà äàííûõ

	int tH = k, tT = s, tF = 0;

	if (k != s) {
		for (int i = 0; i < M; ++i) {
			if (H[i] == tH && T[i] == s) { return F[i]; }
		}

		for (int i = 0; i < M; ++i) {
			if (H[i] == tH) {
				tH = H[i]; tT = T[i];

				tF = F[i];

				cout << tH << " " << tT << " " << tF << endl;
				break;
			}
		}

		for (int j = 0; j < M; ++j) {

			for (int i = 0; i < M; ++i) {
				if (H[i] == tT && T[i] == s) {
					if (tF < F[i]) {
						return tF;
					}else{
						return F[i];
					}

				}
			}

			for (int i = 0; i < M; ++i) {
				if (H[i] == tT) {
					tH = H[i]; tT = T[i];

					if (F[i] < tF)
						tF = F[i];

					cout << tH << " " << tT << " " << tF << endl;
					break;
				}
			}

		}
		//return tF;
	} else {
		return -1;
	}
	cout << endl;
	return 0;
}



int main() {
	/*Ñ÷èòûâàåì äàííûå èç ôàëà î ãðàôå*/

	int N; //÷èñëî âåðøèí
	int M; //÷èñëî ð¸áåð

	string info; //ïåðåìåííàÿ èíôîðìàöèè î òîïîëîãèè íà ýêðàíå

	ifstream f; //âõîäíîé ïîòîê äëÿ ñ÷èòûâàíèÿ äàííûõ èç file.txt
	f.open("file.txt"); //îòêðûâàåì ïîòîê
	f >> N; //ñ÷èòûâàåì ÷èñëî âåðøèí
	info += to_string(N) + " nodes\n\n";

	Graph* Graphs = new Graph[N]; //ñîçäà¸ì N âåðøèí

	for (int i = 0; i < N; i++) { //çàáèâàåì âåðøèíû äàííûìè
		Graphs[i].N = i + 1; //èäåíòèôèêàòîð âåðøèíû
		f >> Graphs[i].x; //êîîðä-û
		f >> Graphs[i].y; //êîîðä-û

		info += "(" + to_string(Graphs[i].N) + ") [" + to_string(Graphs[i].x) + ";" + to_string(Graphs[i].y) + "]\n";
	}

	f >> M; //ñ÷èòûâàåì ÷èñëî ð¸áåð
	info += "\n" + to_string(M) + " links\n\n";

	Link* Links = new Link[M]; //ñîçäà¸ì M ð¸áåð

	int A, B; //âñïîìîãàëêà
	int *H = new int[M]; //äëÿ àëãîðèòìà
	int* T = new int[M];
	int* F = new int[M];

	for (int i = 0; i < M; i++) { //çàáèâàåì ð¸áðà äàííûìè
		Links[i].M = i + 1; //èäåíòèôèêàòîð ðåáðà

		f >> A; //íà÷àëî ðåáðà
		H[i] = A;
		A--; //êîððåêòèðîâêà
		Links[i].A = Graphs[A];

		f >> B; //êîíåö ðåáðà
		T[i] = B;
		B--; //êîððåêòèðîâêà
		Links[i].B = Graphs[B];

		f >> Links[i].F; //ïðîïóñêíàÿ ñïîñîáíîñòü ðåáðà
		F[i] = Links[i].F;

		info += "(" + to_string(Links[i].M) + ") [" + to_string(Graphs[A].N) + ";" + to_string(Graphs[B].N) + "] = " + to_string(Links[i].F) + "\n";
	}

	f.close(); //çàêðûâàåì ïîòîê äàííûõ






	/*Òåêñòîâîå ïîëå äëÿ ãðàôîâ*/

	Font font; //ïåðåìåííàÿ øðèôòà
	font.loadFromFile("arial.ttf"); //ïîäãðóæàåì øðèôò èç ðåñóðñîâ

	Text infoText; //èíôîðìàöèÿ î òîïîëîãèè íà ýêðàíå
	infoText.setCharacterSize(12); //ðàçìåð øðèôòà
	infoText.setFillColor(Color::White); //áåëûé öâåò òåêñòà
	infoText.setFont(font); //ïðèìåíÿåì ïîäãðóæåííûé øðèôò
	infoText.setPosition(20,20); //ïîçèöèîíèðóåì îáúåêò íà ñöåíå
	infoText.setString(info); //çàäà¸ì íà÷àëüíûé òåêñò

	Text istok; //èíôîðìàöèÿ îá èñòîêå
	istok.setCharacterSize(12);
	istok.setFillColor(Color::White);
	istok.setFont(font);
	istok.setPosition(190, 20);
	istok.setString("istok: ");

	Text stok; //èíôîðìàöèÿ î ñòîêå
	stok.setCharacterSize(12);
	stok.setFillColor(Color::White);
	stok.setFont(font);
	stok.setPosition(190, 40);
	stok.setString("stok: ");

	Text answer;  //èíôîðìàöèÿ î ìàêñèìàëüíîì ïîòîêå äàííûõ
	answer.setCharacterSize(12);
	answer.setFillColor(Color::White);
	answer.setFont(font);
	answer.setPosition(190, 60);
	answer.setString("Max flow: ");








	/* Ñîçäàåì è ðñóåì óçëû ãðàôà*/

	Graphs->GraphicNodes = new CircleShape[N]; //êðóã âåðøèíû
	Text* TextNodes = new Text[N]; //íîìåðà âåðøèí

	for (int i = 0; i < N; i++) { //ïåðåáèðàåì âåðøèíû
		Graphs->GraphicNodes[i].setFillColor(Color::Blue); //çàäà¸ì öâåò âåðøèíû
		Graphs->GraphicNodes[i].setRadius(10); //çàäà¸ì ðàäèóñ âåðøèíû
		Graphs->GraphicNodes[i].setPosition((Graphs[i].x * 12) + 500, (Graphs[i].y * 12)+ 150); //ïîçèöèîíèðîâàíèå âåðøèíû

		TextNodes[i].setCharacterSize(10);
		TextNodes[i].setFillColor(Color::White);
		TextNodes[i].setFont(font);
		TextNodes[i].setPosition((Graphs[i].x * 12) + 505, (Graphs[i].y * 12) + 153);
		TextNodes[i].setString(to_string(i+1));
	}


	/*Ñîçäàåì è ðñóåì ðåáðà ãðàôà */

	RectangleShape* GraphicLinks = new RectangleShape[M]; //ïðÿìîóãîëüíèê äëÿ îòðèñîâêè ðåáðà

	for (int i = 0; i < M; i++) { //ïåðåáèðàåì ð¸áðà
		GraphicLinks[i].setFillColor(Color::Yellow);
		float width = sqrtf(powf(Links[i].B.x - Links[i].A.x,2)+ powf(Links[i].B.y - Links[i].A.y, 2)) * 12; //âû÷èñëÿåì ãèïîòåíóçó
		GraphicLinks[i].setSize(Vector2f(width-20, 4)); //çàäà¸ì äëèíó
		float katet = sqrtf(powf(Links[i].B.x - Links[i].A.x, 2) + powf(Links[i].A.y - Links[i].A.y, 2)) * 12; //äëèíà êàòåòà
		float angle;
		if ((Links[i].B.x >= Links[i].A.x) && (Links[i].B.y >= Links[i].A.y)) { //4 êîîðäèíàòíûå ÷åòâåðòè
			angle = acosf(katet / width) * 180 / 3.14; //âû÷èñëÿåì óãîë
			GraphicLinks[i].rotate(angle); //çàäà¸ì óãîë
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160); //ïîçèöèîíèðóåì
		} else if ((Links[i].B.x <= Links[i].A.x) && (Links[i].B.y >= Links[i].A.y)) {
			angle = 180 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		} else if ((Links[i].B.x >= Links[i].A.x) && (Links[i].B.y <= Links[i].A.y)) {
			angle = 360 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		} else if ((Links[i].B.x <= Links[i].A.x) && (Links[i].B.y <= Links[i].A.y)) {
			angle = 270 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		}
	}





	/* Ñîçäàåì è ðèñóåì îêíî */

	RenderWindow window(VideoMode(900, 500), "GRAPHS", Style::Titlebar); //ïåðåìåííàÿ îêíà, çàäà¸ì ðàçìåð è íàçâàíèå îêíà
	int clicks = 0; //äëÿ âûáîðà èñòîêà è ñòîêà
	int I_istok, I_stok; //òåêóùèé èñòîê è ñòîê

	while (window.isOpen()) { //ïîêà îêíî îòêðûòà

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Delete)) {  //çàêðûâàåì îêíî ïî Delete
				window.close();
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) { //ïðîâåðÿåì íàæàòèå íà âåðøèíó
				Graph* clicableNode = NULL; //âðåìåííàÿ ïåðåìåííàÿ
				for (int i = 0; i < N; ++i) {
					if (MouseOnNode(Graphs->GraphicNodes[i], window) && Graphs->GraphicNodes[i].getFillColor() == Color::Red) {
						Graphs->GraphicNodes[i].setFillColor(Color::Blue);
						clicableNode = &Graphs[i];
						if (clicks == 0) {
							istok.setString("istok: " + to_string(clicableNode->N)); //âáèâàåì èñòîê
							I_istok = clicableNode->N;
						}else if (clicks == 1) {
							stok.setString("stok: " + to_string(clicableNode->N)); //âáèâàåì ñòîê
							I_stok = clicableNode->N;
							clicks = -1;

							string s = "Max flow: " + to_string(MAX(I_istok,I_stok,H,T,F,M)); //âû÷èñëÿåì ïðîïóñêíóþ ñïîñîáíîñòü ïîòîêà
							answer.setString(s);
						}
						++clicks;
					} else if(MouseOnNode(Graphs->GraphicNodes[i], window) && Graphs->GraphicNodes[i].getFillColor() == Color::Blue){ //ïîâòîðíîå íàæàòèå íà àêòèâíóþ âåðøèíó
						Graphs->GraphicNodes[i].setFillColor(Color::Red);
						istok.setString("istok: " + to_string(0));
						stok.setString("stok: " + to_string(0));
						answer.setString("Max flow: infinity");
					} else {
						Graphs->GraphicNodes[i].setFillColor(Color::Red);
					}
				}
			}
		}
		//îòðèñîâûâàåì âñ¸

		window.clear(); //î÷èùàåì ýêðàí

		for (int i = 0; i < M; i++) { //îòðèñîâûâàåì ëèíêè
			window.draw(GraphicLinks[i]);
		}

		for (int i = 0; i < N; i++) { //îòðèñîâûâàåì ãðàôû
			window.draw(Graphs->GraphicNodes[i]);
			window.draw(TextNodes[i]);
		}

		window.draw(istok); //îòðèñîâûâàåì òåêñò
		window.draw(stok);
		window.draw(infoText);
		window.draw(answer);

		window.display();
	}

	delete Graphs; //îñâîáîæäàåì äèíàìè÷åñêè âûäåëåííóþ ïàìÿòü
	delete Links;

	return 0;
}

