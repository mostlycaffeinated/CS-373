#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>
#include<vector>

struct State{
	int num;
	std::string type; //accept, reject, start
};
struct Transition{
	int prev_state;
	char prev_sym;
	int new_state;
	char new_sym;
	int shift; //L = -1, R = 1
};

class Turing{
	public:
		State curr_state;
		unsigned int str_pos;
		bool has_blank;

		Turing();
 		void setInpStr(char const* str){
 			INPUT_STR.append(str);
 		};
 		void setMaxTrans(int val){
 			MAX_TRANS = val;
 		};
 		void printResult(){
			std::cout<<RESULT<<"\n";
		};
		void setCurrState(int num);

		void editInpStr(char c,int shift_dir);
		void addState(std::string str);
		void addTrans(std::string str);
		int execute();
		bool blankExists(){
			return has_blank;
		};

	private:
		std::string INPUT_STR;
		std::vector<State> STATES;
		std::vector<Transition> TRANSITIIONS;
		int MAX_TRANS;
		std::string RESULT;
};
