#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <math.h>

class Plane2D {
private:
	size_t rows, cols;
	char line, pnt;
	enum pointState { empty, dot, occupied };
	std::vector<std::vector<pointState>> plane;

public:
	std::vector<std::array<int, 2>> pointsArr;//an array holding all the points made on the plane
	std::vector<std::array<int, 2>> linesArr;//an array holding the indexes of "from-to" points in pointsArr for making lines. eg a line from point 0 to point 1

	Plane2D()//default constructor
		:line('*'), pnt('X'), rows(25), cols(25)
	{
		plane.resize(rows);
		for (int i = 0; i < plane.size(); i++) {
			plane[i].resize(cols);
		}
		clearPlane();
	}

	Plane2D(size_t rows, size_t cols)
		:line('*'), pnt('X'), rows(rows), cols(cols)
	{
		plane.resize(rows);
		for (int i = 0; i < plane.size(); i++) {
			plane[i].resize(cols);
		}
		clearPlane();
	}

	Plane2D(size_t rows, size_t cols, char lineChar, char pointChar)
		:rows(rows), cols(cols), line(lineChar), pnt(pointChar)
	{
		plane.resize(rows);
		for (int i = 0; i < plane.size(); i++) {
			plane[i].resize(cols);
		}
		clearPlane();
	}

	void showSize() {
		int total{ 0 };
		std::cout << plane.size() << std::endl;
		for (int i = 0; i < plane.size(); i++) {
			total += plane[i].size();
		}
		std::cout << total / int(plane.size());
	}

	void drawPlane() {
		for (int i = 0; i < int(rows); i++) {
			for (int j = 0; j < int(cols); j++) {
				if (plane[i][j] == empty) {
					std::cout << "  ";
				}
				else if (plane[i][j] == dot) {
					std::cout << line << " ";
				}
				else if(plane[i][j] == occupied) {
					std::cout << pnt << " ";
				}
			}
			std::cout << std::endl;
		}
	}

	void drawGrid() {
		for (int i = 0; i < int(rows); i++) {
			for (int j = 0; j < int(cols); j++) {
				std::cout << ". ";
	
			}
			std::cout << std::endl;
		}
	}

	void readInPoints(std::string filepath) {
		std::ifstream reader(filepath);
		std::string line1;
		int row, col;

		if (reader.is_open()) {
			while (std::getline(reader, line1)) {
				row = atoi(line1.substr(0, line1.find(" ")).c_str());
				col = atoi(line1.substr(line1.find(" ") + 1, line1.size()).c_str());
				setPoint(row, col);
			}
		}
		reader.close();
	}

	void savePointsTo(std::string filepath) {
		std::ofstream writer(filepath);
		if (writer.is_open()) {
			for (std::array<int, 2>point : pointsArr) {
				writer << point[0] << " " << point[1] << std::endl;
			}
		}
	}

	void readInLines(std::string filepath) {
		std::ifstream reader(filepath);
		std::string line1;
		int indexA, indexB;

		if (reader.is_open()) {
			while (std::getline(reader, line1)) {
				indexA = atoi(line1.substr(0, line1.find(" ")).c_str());
				indexB = atoi(line1.substr(line1.find(" ") + 1, line1.size()).c_str());
				makeLine(pointsArr[indexA], pointsArr[indexB]);
				linesArr.push_back({ indexA, indexB });
			}
		}
		reader.close();
	}

	void saveLinesTo(std::string filepath) {
		std::ofstream writer(filepath);
		if (writer.is_open()) {
			for (std::array<int, 2>line : linesArr) {
				writer << line[0] << " " << line[1] << std::endl;
			}
		}
	}

	void save(std::string saveName) {
		savePointsTo(saveName + "_points.txt");
		saveLinesTo(saveName + "_lines.txt");
	}

	void loadSave(std::string saveName) {
		readInPoints(saveName + "_points.txt");
		readInLines(saveName + "_lines.txt");
	}

	void makeShell() {
		for (int i = 0; i < pointsArr.size(); i++) {
			if (i < pointsArr.size() - 1) {
				makeLine(i, i + 1);
				//linesArr.push_back({ i, i + 1 });
			}
			else {
				makeLine(i, 0);
				//linesArr.push_back({ i, 0 });
			}
		}
	}

	void makeShell(std::vector<std::array<int, 2>>shape) {
		for (int i = 0; i < shape.size(); i++) {
			if (i < shape.size() - 1) {
				makeLine(shape[i], shape[i + 1]);
				//linesArr.push_back({ i, i + 1 });
			}
			else {
				makeLine(shape[i], shape[0]);
				//linesArr.push_back({ i, 0 });
			}
		}
	}

	void printTo(std::string filepath) {
		std::ofstream writer(filepath);

		if (writer.is_open()) {
			for (int i = 0; i < int(rows); i++) {
				for (int j = 0; j < int(cols); j++) {
					if (plane[i][j] == empty) {
						writer << "  ";
					}
					else if (plane[i][j] == dot) {
						writer << line << " ";
					}
					else if (plane[i][j] == occupied) {
						writer << pnt << " ";
					}
				}
				writer << "\n";
			}
		}

		writer.close();

	}

	void setPoint(int row, int col) {
		plane[row][col] = occupied;
		pointsArr.push_back({ row, col });
	}

	void makeLine(std::array<int, 2>pointA, std::array<int, 2>pointB) {//make line from pointA{row, col} to pointB{row, col}
		int rowDiff = pointA[0] - pointB[0];
		int colDiff = pointA[1] - pointB[1];

		if (rowDiff == 0 && colDiff < 0) {//same row, changing cols (to the right)
			for (int j = pointA[1] + 1; j < pointB[1]; j++) {
				plane[pointA[0]][j] = dot;
			}
		}

		else if (rowDiff == 0 && colDiff > 0) { //same row, changing cols (to the left)
			for (int j = pointA[1] - 1; j > pointB[1]; j--) {
				plane[pointA[0]][j] = dot;
			}
		}

		else if (rowDiff < 0 && colDiff == 0) {//same col, changing rows (down)
			for (int i = pointA[0] + 1; i < pointB[0]; i++) {
				plane[i][pointB[1]] = dot;
			}
		}

		else if (rowDiff > 0 && colDiff == 0) {//same col, changing rows (up)
			for (int i = pointA[0] - 1; i > pointB[0]; i--) {
				plane[i][pointB[1]] = dot;
			}
		}

		else if (rowDiff < 0) {//moving down diagonally
			if (abs(rowDiff) == abs(colDiff) && colDiff > 0) {
				int j = pointA[1] - 1;
				for (int i = pointA[0] + 1; i < pointB[0]; i++) {
					plane[i][j] = dot;
					j--;
				}
			}
			else if (abs(rowDiff) == abs(colDiff) && colDiff < 0) {
				int j = pointA[1] + 1;
				for (int i = pointA[0] + 1; i < pointB[0]; i++) {
					plane[i][j] = dot;
					j++;
				}
			}

			else if (abs(rowDiff) < abs(colDiff) && colDiff < 0) {//this is working.
				int colStepStop = 0;
				int colStep = 1;
				for (int i = pointA[0] + 1; i < pointB[0]; i++) {
					plane[i][pointA[1] + colStep] = dot;
					colStepStop = pointA[1] + colStep;
					if (colStep < pointB[1] - 1) {
						colStep++;
					}
				}
				for (int j = pointB[1] - 1; j > colStepStop; j--) {
					plane[pointB[0] - 1][j] = dot;
				}
			}

			else if (abs(rowDiff) > abs(colDiff) && colDiff < 0) {//this is also working.
				int colStep = 1;
				for (int i = pointA[0] + 1; i < pointB[0]; i++) {
					plane[i][pointA[1] + colStep] = dot;
					if (pointA[1] + colStep < pointB[1]) {
						colStep++;
					}
				}
			}

			else if (abs(rowDiff) < abs(colDiff) && colDiff > 0) {//this one too
				int colStepStop = 0;
				int colStep = 1;
				for (int i = pointA[0] + 1; i < pointB[0]; i++) {
					plane[i][pointA[1] - colStep] = dot;
					colStepStop = pointA[1] - colStep;
					if (pointB[1] + colStep < pointA[1] - 1) {
						colStep++;
					}
				}
		
				for (int j = pointB[1] + 1; j < colStepStop; j++) {
					plane[pointB[0] - 1][j] = dot;
				}
			}
			else if (abs(rowDiff) > abs(colDiff) && colDiff > 0) {//this one too
				int colStep = 1;
				for (int i = pointA[0] + 1; i < pointB[0]; i++) {
					plane[i][pointA[1] - colStep] = dot;
					if (pointA[1] - colStep > pointB[1]) {
						colStep++;
					}
				}
			}
		}

		else if (rowDiff > 0) {//moving up diagonally
			if (abs(rowDiff) == abs(colDiff) && colDiff < 0) {
				int j = pointA[1] + 1;
				for (int i = pointA[0] - 1; i > pointB[0]; i--) {
					plane[i][j] = dot;
					j++;
				}
			}

			else if (abs(rowDiff) == abs(colDiff) && colDiff > 0) {
				int j = pointA[1] - 1;
				for (int i = pointA[0] - 1; i > pointB[0]; i--) {
					plane[i][j] = dot;
					j--;
				}
			}

			else if (abs(rowDiff) < abs(colDiff) && colDiff < 0) {//this is working.
				int colStepStop = 0;
				int colStep = 1;
				for (int i = pointA[0] - 1; i > pointB[0]; i--) {
					plane[i][pointA[1] + colStep] = dot;
					colStepStop = pointA[1] + colStep;
					if (colStep < pointB[1] - 1) {
						colStep++;
					}
				}
				for (int j = pointB[1] - 1; j > colStepStop; j--) {
					plane[pointB[0] + 1][j] = dot;
				}
			}

			else if (abs(rowDiff) > abs(colDiff) && colDiff < 0) {//this is also working.
				int colStep = 1;
				for (int i = pointA[0] - 1; i > pointB[0]; i--) {
					plane[i][pointA[1] + colStep] = dot;
					if (pointA[1] + colStep < pointB[1]) {
						colStep++;
					}
				}
			}

			else if (abs(rowDiff) < abs(colDiff) && colDiff > 0) {//this one too
				int colStepStop = 0;
				int colStep = 1;
				for (int i = pointA[0] - 1; i > pointB[0]; i--) {
					plane[i][pointA[1] - colStep] = dot;
					colStepStop = pointA[1] - colStep;
					if (pointB[1] + colStep < pointA[1] - 1) {
						colStep++;
					}
				}
		
				for (int j = pointB[1] + 1; j < colStepStop; j++) {
					plane[pointB[0] + 1][j] = dot;
				}
			}
			else if (abs(rowDiff) > abs(colDiff) && colDiff > 0) {//this one too
				int colStep = 1;
				for (int i = pointA[0] - 1; i > pointB[0]; i--) {
					plane[i][pointA[1] - colStep] = dot;
					if (pointA[1] - colStep > pointB[1]) {
						colStep++;
					}
				}
			}
			
		}

		//adding point indexes to linesArr
		for (int i = 0; i < pointsArr.size(); i++) {
			if (pointA == pointsArr[i]) {
				for (int j = 0; j < pointsArr.size(); j++) {
					if (pointB == pointsArr[j]) {
						linesArr.push_back({ i, j });
					}
				}
			}
		}
	}

	void makeLine(int pointsArrIndexA, int pointsArrIndexB) {//makes lines using the indexes for points in pointsArr
		std::array<int, 2>pointA, pointB;
		//linesArr.push_back({ pointsArrIndexA,pointsArrIndexB });

		pointA = pointsArr[pointsArrIndexA];
		pointB = pointsArr[pointsArrIndexB];

		makeLine(pointA, pointB);
	}

	void removePoint(int row, int col) {
		plane[row][col] = empty;
	}

	void clearPlane() {
		for (int i = 0; i < int(rows); i++) {
			for (int j = 0; j < int(cols); j++) {
				plane[i][j] = empty;
			}
		}

		pointsArr.clear();
		linesArr.clear();
	}
};
