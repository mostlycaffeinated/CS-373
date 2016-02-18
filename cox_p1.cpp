#include<fstream>
#include<iomanip>
#include<stdexcept>
#include"cox_p1.h"

Turing::Turing(){
	has_blank = false;
	str_pos  = 0;
	RESULT = "";
	INPUT_STR = "";
	curr_state.num = -1;
	MAX_TRANS = 10000;
}
void Turing::editInpStr(char symbol, int shift_dir){
	INPUT_STR[str_pos] = symbol;
	if((shift_dir == -1)&&(str_pos == 0)){
		str_pos = INPUT_STR.length()-1;
	}else if((shift_dir == 1)&&(str_pos == INPUT_STR.length()-1)){
		str_pos = 0;
	}else{
		str_pos += shift_dir;
	}
}
void Turing::addState(std::string line){
	State s;
	std::string junk;
	std::istringstream ss(line);
	ss>>junk;
	ss>>s.num;
	ss>>s.type;
	if(!(s.type).compare("start")){
		curr_state.num = s.num;
		curr_state.type = "start";
	}
	STATES.push_back(s);
}
void Turing::addTrans(std::string line){
	Transition t;
	std::string junk;
	char direction;
	std::istringstream ss(line);
	ss>>junk;
	ss>>t.prev_state;
	ss>>t.prev_sym;
	if(t.prev_sym == '_'){
		has_blank = true;
	}
	ss>>t.new_state;
	ss>>t.new_sym;
	ss>>direction;
	if(direction == 'L'){
		t.shift = -1;
	}else{
		t.shift = 1;
	}
	TRANSITIIONS.push_back(t);
}
void Turing::setCurrState(int num){
	curr_state.num = num;
	for(unsigned int i = 0; i < STATES.size(); ++i){
		if(STATES.at(i).num == num){
			curr_state.type = STATES.at(i).type;
			break;
		}
	}
}
int Turing::execute(){
	int trans_num = 0;
	RESULT.append(std::to_string(curr_state.num));
	while(trans_num < MAX_TRANS){
		char sym = INPUT_STR[str_pos];
		RESULT.append("->");
		for(unsigned int i = 0; i < TRANSITIIONS.size(); ++i){
			if((TRANSITIIONS.at(i).prev_state == curr_state.num)&&(TRANSITIIONS.at(i).prev_sym == sym)){
				setCurrState(TRANSITIIONS.at(i).new_state);
				editInpStr(TRANSITIIONS.at(i).new_sym,TRANSITIIONS.at(i).shift);
				break;
			}
		}
		++trans_num;
		if((!(curr_state.type).compare("accept"))||(!(curr_state.type).compare("reject"))){
			RESULT.append(std::to_string(curr_state.num));
			break;
		}else if(trans_num == MAX_TRANS){
			curr_state.type = "quit";
		}
		RESULT.append(std::to_string(curr_state.num));
	}
	RESULT.append(" ");
	RESULT.append(curr_state.type);
	RESULT.append(" ");
	return 0;
}

int main(int argc, char* argv[]){
	if(argc < 3){
		std::cerr<<"Usage: "<<argv[0]<<" <input file> <input string> <max transitions>\n";
		return -1;
	}else{
		Turing machine;
		machine.setInpStr(argv[2]);
		if(argc == 4){
			machine.setMaxTrans(atoi(argv[3]));
		}

		std::ifstream inp(argv[1]);
		if(inp){
			//set up machine
			std::string line;
			while(std::getline(inp,line)){
				std::istringstream ss(line);
				std::string type;	
				ss>>type;
				if(!type.compare("state")){
					machine.addState(line);
				}else{
					machine.addTrans(line);
				}
			}
			//run machine
			if(machine.blankExists()){
				machine.setInpStr("__");
			}
			machine.execute();
			machine.printResult();
		}else{
			std::cerr<<"Error reading file "<<argv[1]<<std::endl;
			return -1;
		}
		inp.close();
	}
	return 0;
}
