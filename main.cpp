#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum state { Out_Of_Poptart, No_Credit, Has_Credit, Dispenses_Poptart }; //Enum states that will allow the implementation of the State design pattern
enum stateParameter { No_Of_Poptarts, Credit, Cost_Of_Poptart }; //enum for the state parameters which will allow values to be stored.

class StateContext;

class State //this is the class that will hold and maintain the current state
{
protected:

	StateContext* CurrentContext; // this is a reference from another class which is called StateContext

public:

	State(StateContext* Context)
	{
		CurrentContext = Context;
	}
	virtual ~State(void) {} // destructor for the class state
	virtual void transition(void) {} // this will handle the transitions of the vending machine
};

class StateContext //this class will get and set the states that will be changing
{
protected:

	State* CurrentState = nullptr; // this pointer has been set to nullptr
	int stateIndex = 0; // state index has been set to the value of 0
	vector<State*> availableStates; // this will be the vector that will allow the machine to change states
	vector<int> stateParameters; // this stores the enum state parameter values within a vector for essential use

public:
	virtual ~StateContext(void); //destructor for the class statecontext
	virtual void setState(state newState); //this sets a new state
	virtual int getStateIndex(void); // this will get the value within stateindex
	virtual void setStateParam(stateParameter SP, int value); //this gives the machine the ability to change the values for the enum state parameters with values of its choice
	virtual int getStateParam(stateParameter SP); // this will get the values from the state parameter
};

StateContext::~StateContext(void) //destructor for the statecontext class
{
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i]; //for loop to execute clearing code
	this->availableStates.clear(); // clears the states to release held memory
	this->stateParameters.clear(); // clears the state parameters to release held memory
}

void StateContext::setState(state newState) // this will make the current state a new available state
{
	this->CurrentState = availableStates[newState];
	this->stateIndex = newState; //state index will now equal the new state
	this->CurrentState->transition(); //this is used to transition the states when required
}

int StateContext::getStateIndex(void) // gets the state index
{
	return this->stateIndex; //returns the stateindex
}

void StateContext::setStateParam(stateParameter SP, int value) //this sets the state parameters
{
	this->stateParameters[SP] = value; // state parameters are equal to value which is decided by the user
}

int StateContext::getStateParam(stateParameter SP) // this gets the state parameter values
{
	return this->stateParameters[SP]; // returns the state parameter values
}

class Transition // transition class to maneouver the different states
{
public:
	virtual bool insertMoney(int) { cout << "Error!" << endl; return false; } // insert money method, will cause error if used this way
	virtual bool makeSelection(int) { cout << "Error!" << endl; return false; }// make selection method, will cause error if used this way
	virtual bool moneyRejected(void) { cout << "Error!" << endl; return false; }// money rejected method, will cause error
	virtual bool addPoptart(int) { cout << "Error!" << endl; return false; }//addpoptart method, will cause error
	virtual bool dispense(void) { cout << "Error!" << endl; return false; }//dispense error, will cause error
};

class PoptartState : public State, public Transition //poptart state class that inherits from state class and transition class
{
public:
	PoptartState(StateContext* Context) : State(Context) {}
};

class OutOfPoptart : public PoptartState //out of poptart class that inherits from poptart state
{
public:
	OutOfPoptart(StateContext* Context) : PoptartState(Context) {} // these functions will be called if this is the selected state which is done by the user
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

class NoCredit : public PoptartState //no credit class that inherits from poptartstate
{
public:
	NoCredit(StateContext* Context) : PoptartState(Context) {} // will call these functions if this state is the active state
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

class HasCredit : public PoptartState //has credit class that inherits from poptartstate
{
public:
	HasCredit(StateContext* Context) : PoptartState(Context) {} // will call these functions if this state is the active state
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

class DispensesPoptart : public PoptartState //dispensespoptart class that inherits from poptartstate
{
public:
	DispensesPoptart(StateContext* Context) : PoptartState(Context) {} // will call these functions if this state is the active state
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

class Product //product class that will contain the details of the poptart
{
	friend class Filling; // filling class prototype if you want to include fillings
protected:
	string product_description; // string for the description of the product
	int itemCost = 0; // itemcost so you can store the value of the poptart
public:
	virtual void consume(void); //virtual void consume function to eat the dispensed poptart
	virtual int cost(void); // function to use the cost of the poptart
	virtual string description(void); // function to use the product description
};

void Product::consume(void) // consume function
{
	cout << "Consumed: " << this->description() << " | " << "Price: " << this->cost() << endl;
	delete this;
}

int Product::cost(void) //cost function
{
	return this->itemCost; //returns the itemcost
}

string Product::description(void) //function to utilize the description
{
	return this->product_description; //returns product description
}

class Poptart : public Product //poptart class that inherits from product
{
public:
	Poptart(void)
	{
		this->product_description = "Poptart"; //uses product description and calls the string "Poptart"
		this->itemCost = 50; //this adds a price of the product
	}
};

class Plainbase : public Poptart //plain base class that inherits from poptart
{
public:
	Plainbase(void)
	{
		this->product_description = "Plain"; // plain is inserted into product description
		this->itemCost = 100; // 100 is inserted into itemcost
	}
};

class Spicybase : public Poptart //spicy base class that inherits from poptart
{
public:
	Spicybase(void)
	{
		this->product_description = "Spicy"; //spicy is inserted into product description
		this->itemCost = 150; //150 is inserted into itemcost
	}
};

class Chocolatebase : public Poptart //Chocolatebase class that inherits from poptart
{
public:
	Chocolatebase(void)
	{
		this->product_description = "Chocolate"; //chocolate is inserted into the product description
		this->itemCost = 200; //200 is inserted into the itemcost
	}
};

class Coconutbase : public Poptart //coconut base class that inherits from the poptart class
{
public:
	Coconutbase(void)
	{
		this->product_description = "Coconut"; //coconut is inserted into the product description
		this->itemCost = 200; //200 is inserted into item cost
	}
};

class Fruitybase : public Poptart //fruity base class that inherits from the poptart class
{
public:
	Fruitybase(void)
	{
		this->product_description = "Fruity"; //fruity is inserted into the product description
		this->itemCost = 200; //200 is inserted into item cost
	}
};

class Poptart_Dispenser : public StateContext, public Transition //poptart dispenser class that inherits from statecontext and transition class
{
	friend class DispensesPoptart; //gives this class the ability to use the dispenses poptart class
	friend class HasCredit; //gives this class the ability to use the Has credit class
private:
	PoptartState* PoptartCurrentState = nullptr; //pointer has been set to nullptr
	bool itemDispensed = false; 
	//indicates whether a product is there to be retrieved
	Product* DispensedItem = nullptr;
	bool itemRetrieved = false; //indicates whether a product has been retrieved
public:
	Poptart_Dispenser(int inventory_count);//will be used to see how many poptarts are in the machine
	~Poptart_Dispenser(void);
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
	Product* getProduct(void); // useful since you need this to see if the product has been dispensed
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP);
};

// --------------------------------------------------------- OUT OF POPTART START --------------------------------------------------------- //
bool OutOfPoptart::insertMoney(int money) //insert money in the outofpoptart state
{
	cout << "ERROR! NO POPTARTS AVAILABLE!" << endl; // error since youre not allowed
	return false;
}

bool OutOfPoptart::makeSelection(int option)// cant make selection in this state
{
	cout << "No Poptarts available, cannot make a selection!" << endl;
	return false;
}
bool OutOfPoptart::moneyRejected(void) //ejects money
{
	cout << "Ejecting Money!" << endl;
	return false;
}
bool OutOfPoptart::addPoptart(int number)//adds poptarts depending on the inputted amount
{
	this->CurrentContext->setStateParam(No_Of_Poptarts, number);//uses the stateparam and integer to add poptarts
	cout << number << " Poptart has been added to the machine!" << endl; //cout to tell people that poptarts have been added
	cout << "--------------------------------------" << endl;
	this->CurrentContext->setState(No_Credit); //sets current state to no credit
	return true;
}
bool OutOfPoptart::dispense(void) //cant dispense when there is no poptarts
{
	cout << "Machine has ran out of Poptarts, nothing to dispense!" << endl;
	return false;
}
// --------------------------------------------------------- OUT OF POPTART END --------------------------------------------------------- //

// --------------------------------------------------------- NO CREDIT START --------------------------------------------------------- //
bool NoCredit::insertMoney(int money) //function to insert money
{
	cout << "Money Inserted: " << money << endl;//cout to show the amount of inserted money
	this->CurrentContext->setStateParam(Credit, money); //set stateparam and integer to specfied amount
	cout << "Current Balance: " << money << endl; //displayed current balance
	this->CurrentContext->setState(Has_Credit); //changes state to has credit
	return true;
}

bool NoCredit::makeSelection(int option) //cant make selection here
{
	cout << "You have inserted no money!" << endl;
	return false;
}

bool NoCredit::moneyRejected(void) //money has been rejected in this state
{
	cout << "Money has been rejected!" << endl;
	return false;
}

bool NoCredit::addPoptart(int number) //cannot add poptarts in this state
{
	cout << "ERROR! You already have a Poptart!" << endl;
	return false;
}

bool NoCredit::dispense(void) // cannot dispense anything since you have inserted no money
{
	cout << "ERROR! You have inserted no money!" << endl;
	return false;
}
// --------------------------------------------------------- NO CREDIT END --------------------------------------------------------- //

// --------------------------------------------------------- HAS CREDIT START --------------------------------------------------------- //
bool HasCredit::insertMoney(int money) //can insert more money in this state if you wish
{
	cout << "Money Inserted: " << money << endl; //displays balance
	money += CurrentContext->getStateParam(Credit); //adds money to current balance
	this->CurrentContext->setStateParam(Credit, money); //set stateparam and money integer to current balance
	cout << "Current Balance: " << money << endl; //displays new balance
	this->CurrentContext->setState(Has_Credit); // set state to has credit
	return true;
}

bool HasCredit::makeSelection(int option) //make selection function that will select the base that you want
{
	switch (option) //switch that uses option as a value
	{
	case(1): // 1 for plain base
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Plainbase; //gives access to information within the private class and plain base poptart is created
		cout << "Plain base chosen!" << endl;
		break;
	case(2): // 2 for spicy base
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Spicybase;
		cout << "Spicy base chosen!" << endl;
		break;
	case(4): // 4 for chocolate base
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Chocolatebase;
		cout << "Chocolate base chosen!" << endl;
		break;
	case(8): // 8 for coconut base
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Coconutbase;
		cout << "Coconut base chosen!" << endl;
		break;
	case(16): //16 for fruity base
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Fruitybase;
		cout << "Fruity base chosen!" << endl;
		break;
	default:
		cout << "Invalid/No Selection has been made!" << endl;

		
		
	}
	this->CurrentContext->setState(Dispenses_Poptart); //sets the current state to dispenses poptart
	return true;
}

bool HasCredit::moneyRejected(void) //rejects money function within the has credit state
{
	cout << "ERROR! Money has been rejected!" << endl;
	this->CurrentContext->setStateParam(Credit, 0); //sets credit to 0
	this->CurrentContext->setState(No_Credit); //changes state to no credit
	return true;
}

bool HasCredit::addPoptart(int number) //tries to add a poptart in the wrong state
{
	cout << "ERROR! You already have a Poptart!" << endl;
	return false;
}

bool HasCredit::dispense(void) //tries to dispense in the wrong state
{
	cout << "ERROR! Cannot dispense poptart!" << endl;
	return false;
}
// --------------------------------------------------------- HAS CREDIT END --------------------------------------------------------- //

// --------------------------------------------------------- DISPENSE POPTART START --------------------------------------------------------- //
bool DispensesPoptart::insertMoney(int money) //tries to insert money in the wrong state
{
	cout << "ERROR! Cannot increase balance at this point!" << endl;
	return false;
}

bool DispensesPoptart::makeSelection(int option) // tries to make a selection in the wrong state
{
	cout << "ERROR! Cannot select a poptart at this point!" << endl;
	return false;
}

bool DispensesPoptart::moneyRejected(void) // function which will reject money
{
	cout << "Money has been rejected!" << endl;
	return false;
}

bool DispensesPoptart::addPoptart(int number) //  tries to add a poptart in the wrong state
{
	cout << "ERROR! You already have a Poptart!" << endl;
	return false;
}

bool DispensesPoptart::dispense(void) // this function will allow the machine to dispense poptarts
{
	
	((Poptart_Dispenser*)(this->CurrentContext))->itemDispensed = true; //states the item has been dispensed
	
	if (this->CurrentContext->getStateParam(No_Of_Poptarts) == 0) //if poptarts = 0, change state to out of poptart
		this->CurrentContext->setState(Out_Of_Poptart);

	else if (this->CurrentContext->getStateParam(No_Of_Poptarts) > 0 && this->CurrentContext->getStateParam(Credit) == 0) // if you have more than 1 poptart but no money, go to no credit state
		this->CurrentContext->setState(No_Credit);

	else if (this->CurrentContext->getStateParam(Credit) < this->CurrentContext->getStateParam(Cost_Of_Poptart)) // if you have less credit than your current selection, change state to has credit
		this->CurrentContext->setState(Has_Credit);

	else if (this->CurrentContext->getStateParam(No_Of_Poptarts) > 0 && this->CurrentContext->getStateParam(Credit) > 0) // if there is 1 or more poptarts in the machine and you have enough money to purchase, return to has credit state
		this->CurrentContext->setState(Has_Credit);

	this->CurrentContext->setStateParam(No_Of_Poptarts, this->CurrentContext->getStateParam(No_Of_Poptarts) - 1); //removes 1 from the number or poptarts enum

	this->CurrentContext->setStateParam(Credit, this->CurrentContext->getStateParam(Credit) - this->CurrentContext->getStateParam(Cost_Of_Poptart)); //takes away the cost of the poptart from your balance

	cout << ((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem->description() << " Poptart has been dispensed!" << endl; //declare that the poptart has been dispensed using the description function
	
	
	cout << "Current Balance: " << this->CurrentContext->getStateParam(Credit) << endl; //displays current balance by using the getstateparam
	cout << "--------------------------------------" << endl;
	

	return true;
}
// --------------------------------------------------------- DISPENSE POPTART END --------------------------------------------------------- //

Poptart_Dispenser::Poptart_Dispenser(int inventory_count) //poptart dispenser that uses inventory count within the parameter
{//this allows the states to be changed by the use of pushing back with the vector. This also shows the first state
	this->availableStates.push_back(new OutOfPoptart(this));
	this->availableStates.push_back(new NoCredit(this));
	this->availableStates.push_back(new HasCredit(this));
	this->availableStates.push_back(new DispensesPoptart(this));
	this->stateParameters.push_back(0);
	this->stateParameters.push_back(0);

	this->setState(Out_Of_Poptart); // this is the "default" state
	if (inventory_count > 0) //if this integer is more than 0, use it to add poptarts
	{
		this->addPoptart(inventory_count); 
	}
}

Poptart_Dispenser::~Poptart_Dispenser(void) //destructor for the poptart dispenser class
{
	if (!this->itemRetrieved)//if item is retrieved, delete dispensed item
	{
		delete this->DispensedItem;
	}
}

bool Poptart_Dispenser::insertMoney(int money) // this function will allow the use of all the insert money functions for each state, which will give you a different output depending on your current state.
{
	PoptartCurrentState = (PoptartState*) this->CurrentState; //gets current state and outputs function
	return this->PoptartCurrentState->insertMoney(money);
}

bool Poptart_Dispenser::makeSelection(int option)// this function will allow the use of all the make selection functions for each state, which will give you a different output depending on your current state.
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;//gets current state and outputs function
	return this->PoptartCurrentState->makeSelection(option);
}

bool Poptart_Dispenser::moneyRejected(void)// this function will allow the use of all the money rejected functions for each state, which will give you a different output depending on your current state.
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;//gets current state and outputs function
	return this->PoptartCurrentState->moneyRejected();
}

bool Poptart_Dispenser::addPoptart(int number)// this function will allow the use of all the add poptart functions for each state, which will give you a different output depending on your current state.
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;//gets current state and outputs function
	return this->PoptartCurrentState->addPoptart(number);
}

bool Poptart_Dispenser::dispense(void)// this function will allow the use of all the dispense functions for each state, which will give you a different output depending on your current state.
{
	PoptartCurrentState = (PoptartState*) this->CurrentState;//gets current state and outputs function
	return this->PoptartCurrentState->dispense();
}

Product* Poptart_Dispenser::getProduct(void) // this will be used to show if the product has been retrieved, 
{
	if (this->itemDispensed)
	{
		this->itemDispensed = false;//if item has been dispensed, dispense is false and retrieved is true
		this->itemRetrieved = true;
		return this->DispensedItem;
	}

	return nullptr;
}
void Poptart_Dispenser::setStateParam(stateParameter SP, int value) //this will change the values of the state parameter of number of poptarts and credit (Due to SP)
{
	if (SP == Cost_Of_Poptart) return;
	this->stateParameters[SP] = value;
}

int Poptart_Dispenser::getStateParam(stateParameter SP)//this function returns the values within the state parameters
{
	if (SP == Cost_Of_Poptart)
	{
		if (DispensedItem == nullptr) return 0;
		return DispensedItem->cost();
	}
	return this->stateParameters[SP];
}
