#pragma once
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>


class Utility
{
public:
	static std::set<int> WriteHighScore(int score)
	{
		// see if file exists and read values
		std::string fileName = "highscores.txt";
		std::ifstream highscoreFile(fileName);
		std::istream_iterator<int> start(highscoreFile), end;
		std::set<int> highscores(start, end);
		highscoreFile.close();

		//if its empty, it means it didnt exist and so we want to populate and save it
		if (highscores.size() == 0)
		{
			highscores.insert(100);
			highscores.insert(50);
			highscores.insert(20);
			highscores.insert(10);
			highscores.insert(5);

			std::ofstream outfile(fileName);
			std::ostream_iterator<int> output_iterator(outfile, "\n");
			std::copy(highscores.begin(), highscores.end(), output_iterator);
			outfile.close();
		}

		// write the score
		highscores.insert(score);


		// remove the lowest score
		highscores.erase(highscores.begin());

		// write the highscores and save again.
		std::ofstream outfile(fileName);
		std::ostream_iterator<int> output_iterator(outfile, "\n");
		std::copy(highscores.begin(), highscores.end(), output_iterator);
		outfile.close();

		return highscores;
	}


};
