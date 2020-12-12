#include <iostream>
#include <string>
#include "Plane2D.h"

void cubeExample();
void menu(Plane2D& canvas);
void plotPoints(Plane2D& canvas);
void drawLines(Plane2D& canvas);
void savePlane(Plane2D& canvas);
void loadFiles(Plane2D& canvas);
std::array<int, 2>parseInput(std::string& input);

int main() {
	std::string input;
	std::array<int, 2>parsedVals;

	std::cout << "Enter plane dimensions: ";
	std::cout << "\n>";
	std::getline(std::cin, input);
	parsedVals = parseInput(input);

	Plane2D canvas(parsedVals[0], parsedVals[1]);

	menu(canvas);
	std::cin.get();

	return 0;
}

void cubeExample() {
	Plane2D Cplane(25, 25);

	std::vector<std::array<int, 2>> shape = {
		{4, 6},//0
		{4, 16},//1
		{14, 16},//2
		{14, 6}//3	
	};

	std::vector<std::array<int, 2>> shape2 = {
		{10, 12},
		{10, 22},
		{20, 22},
		{20, 12}
	};

	for (std::array<int, 2>point : shape) {
		Cplane.setPoint(point[0], point[1]);
	}

	Cplane.makeShell(shape);

	for (std::array<int, 2>point : shape2) {
		Cplane.setPoint(point[0], point[1]);
	}

	Cplane.makeShell(shape2);


	for (int i = 0; i < shape.size(); i++) {
		Cplane.makeLine(shape[i], shape2[i]);
	}

	Cplane.drawPlane();
	Cplane.save("Cube3D");
	Cplane.printTo("plainShape.txt");

	std::cout << "Saved as 'Cube3D', and printed to 'plainShape.txt'" << std::endl;
	std::cin.get();
}

std::array<int, 2>parseInput(std::string& input) {
	char seperator{ ',' };
	int num1, num2;
	if (input.find(",") != input.npos) {
		seperator = ',';
	}
	else if (input.find(":") != input.npos) {
		seperator = ':';
	}

	num1 = atoi(input.substr(0, input.find(seperator)).c_str());
	num2 = atoi(input.substr(input.find(seperator) + 1, input.size()).c_str());
	std::array<int, 2>arr{ num1, num2 };

	return arr;
}

void plotPoints(Plane2D& canvas) {
	std::string input;
	int i = 0;
	std::array<int, 2>parsedVals;

	while (true) {
		system("cls");
		if (i != 0) {
			canvas.drawPlane();
			std::cout << std::endl;
		}
		std::cout << "Set point (row, col): ";
		std::cout << "\n>";
		std::cin >> input;

		if (input.find("exit") != input.npos || input.find("Exit") != input.npos) {
			break;
		}

		parsedVals = parseInput(input);
		canvas.setPoint(parsedVals[0], parsedVals[1]);
		canvas.drawPlane();

		i++;
		std::cout << std::endl;
		system("pause");
	}

	std::cout << std::endl;
	system("pause");
	menu(canvas);
}

void drawLines(Plane2D& canvas) {
	system("cls");
	canvas.drawPlane();

	std::string input;
	int i = 0;
	std::array<int, 2> pointAB;

	std::cout << std::endl << std::endl;
	std::cout << "*** try entering 'shell' or 'makeShell' ***" << std::endl;

	while (true) {
		if (i != 0) {
			canvas.drawPlane();
			std::cout << std::endl;
		}
		std::cout << "From point - To point: ";
		std::cout << "\n>";
		std::cin >> input;
		if (input.find("exit") != input.npos || input.find("Exit") != input.npos) {
			break;
		}

		else if (input.find("makeShell") != input.npos || input.find("shell") != input.npos) {
			canvas.makeShell();
		}

		else {
			pointAB = parseInput(input);
			canvas.makeLine(pointAB[0], pointAB[1]);
		}

		i++;
		canvas.drawPlane();
		//std::cout << std::endl << std::endl;
		system("pause");
		system("cls");
	}

	std::cout << std::endl << std::endl;
	system("pause");
	menu(canvas);
}

void savePlane(Plane2D& canvas) {
	system("cls");
	canvas.drawPlane();
	std::string saveName;

	std::cout << "Project Save: " << std::endl;
	std::cout << ">";
	std::cin >> saveName;

	canvas.save(saveName);
	std::cout << std::endl << std::endl;
	system("pause");
	menu(canvas);
}

void loadFiles(Plane2D& canvas) {
	system("cls");
	std::string saveName;
	std::cout << "Load project save: " << std::endl;
	std::cout << ">";
	std::cin >> saveName;

	canvas.loadSave(saveName);
	canvas.drawPlane();
	std::cout << std::endl << std::endl;
	system("pause");
	menu(canvas);
}

void menu(Plane2D& canvas) {
	using namespace std;
	system("cls");
	string filename;
	int optn;

	cout << "Menu: " << endl;
	cout << "1.Load in files," << endl;
	cout << "2.Set points," << endl;
	cout << "3.Draw lines," << endl;
	cout << "4.Save plane," << endl;
	cout << "5.printTo," << endl;
	cout << "6.Show cube example," << endl;
	cout << "7.Exit." << endl;
	cout << ">";

	cin >> optn;

	switch (optn) {
	case 1:
		loadFiles(canvas);
		break;
	case 2:
		plotPoints(canvas);
		break;
	case 3:
		drawLines(canvas);
		break;
	case 4:
		savePlane(canvas);
		break;
	case 5:
		system("cls");
		cout << "Save Sketch to:" << endl;
		cout << ">";
		cin >> filename;
		canvas.printTo(filename);
		system("pause");
		menu(canvas);
		break;
	case 6:
		cubeExample();
		break;
	case 7:
		exit(0);
		break;

	default:
		cout << "\n\nInvalid Input!\n\n";
		system("pause");
		menu(canvas);
		break;
	}
}
