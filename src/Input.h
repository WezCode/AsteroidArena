#pragma once
#ifndef INPUT_H
#define INPUT_H

enum class Key { W, A, D};

class Input {

	public:
		Input();
		~Input();

		bool getKeyPressed(Key k);
		void setKeyPressed(Key k, bool value);


	private:
		bool wKeyPressed;
		bool aKeyPressed;
		bool dKeyPressed;

};


#endif