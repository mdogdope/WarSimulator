#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class Card
{
private:
	int suit = 0;
	int value = 0;
public:
	Card(int s, int v)
	{
		suit = s;
		value = v;
	}
	
	int getSuit()
	{
		return suit;
	}
	
	int getValue()
	{
		return value;
	}
};

class Player
{
private:
	vector<Card> hand = {};
public:
	void add(Card card)
	{
		hand.push_back(card);
	}
	
	int getSize()
	{
		return hand.size();
	}
	
	bool hasCards()
	{
		return hand.empty();
	}
	
	Card getTop()
	{
		Card temp = hand.at(0);
		hand.erase(hand.begin());
		return temp;
	}
	
	void shuffle()
	{
		vector<Card> temp = {};
		while(!hand.empty())
		{
			int index = rand() % hand.size();
			temp.push_back(hand.at(index));
			hand.erase(hand.begin() + index);
		}
	
		hand = temp;
		
	}
};

void play(vector<Player> ps)
{
	
	vector<Player> players = {};
	
	for(int i = 0; i < ps.size(); i++)
	{
		players.push_back(ps[i]);
	}
	
//	cout << players.size();
	
	bool gameOver = false;
	
	int counter = 0;
	
	while(!gameOver)
	{
		vector<Card> inPlay = {};
		
		int highPlayer = 0;
		int highCard = 0;
		for(int i = 0; i < players.size(); i++)
		{
			Card temp = players[i].getTop();
			
			inPlay.push_back(temp);
			
			if(temp.getValue() > highCard)
			{
				highCard = temp.getValue();
				highPlayer = i;
			}
		}
		
		int matchingVals = 0;
		
		for(int i = 0; i < inPlay.size(); i++)
		{
			if(inPlay[i].getValue() == highCard)
			{
				matchingVals++;
			}
		}
		
		if(players.size() != 2)
		{
			int turns = rand() % (1000 / players.size());
			
			counter = turns + 36;
			
			break;
		}
		
		if(matchingVals >= 2)
		{
			continue;
		}
		
//		if(counter % 1000 == 0)
//		{
//			cout << "##### " << inPlay[0].getValue() << "|" << inPlay[1].getValue() << endl;
//		}
//		
//		if(counter % 1001 == 0)
//		{
//			cout << "==##### " << inPlay[0].getValue() << "|" << inPlay[1].getValue() << endl;
//		}
		
		for(int i = 0; i < inPlay.size(); i++)
		{
			players[highPlayer].add(inPlay[i]);
		}
		
		vector<Player> tempPlayers = {};
		for(int  i = 0; i < players.size(); i++)
		{
			if(players[i].hasCards()){
				tempPlayers.push_back(players[i]);
			}
		}
		
		for(int i = 0; i < tempPlayers.size(); i++)
		{
			players.push_back(tempPlayers[i]);
		}
		
		if(players.size() <= 1)
		{
			gameOver = true;
		}
		
		if(counter >= 1000)
		{
			cout << "Finished round " << counter << " " << players[0].getSize() << endl;
		}
		
		counter++;
		
	}
	
	cout << endl << "This game took: " << counter << " turns!" << endl;
	
	
}

void start(int deckCount, int playerCount)
{
	vector<Player> players = {};
	vector<Card> deck = {};
	
	for(int i = 0; i < deckCount; i++)
	{
		for(int is = 1; is <= 4; is++)
		{
			for(int iv = 1; iv <= 13; iv++)
			{
				Card c(is, iv);
				deck.push_back(c);
			}
		}
	}
	
	srand(time(NULL));
	
	
	vector<Card> buffDeck = {};
	while(!deck.empty())
	{
		int index = rand() % deck.size();
		buffDeck.push_back(deck.at(index));
		deck.erase(deck.begin() + index);
	}
	
	deck = buffDeck;
	
//	for(int i = 0; i < deck.size(); i++)
//	{
//		cout << to_string(deck.at(i).getSuit()) + "|" + to_string(deck.at(i).getValue()) << endl;
//	}
	
	for(int i = 0; i < playerCount; i++)
	{
		players.push_back(Player());
	}
	
//	cout << players.size();
	
	while(!deck.empty())
	{
		for(int ip = 0; ip < players.size(); ip++)
		{
			if(!deck.empty())
			{
				players[ip].add(deck.at(0));
				deck.erase(deck.begin());
			}
		}
	}
	
//	for(int i = 0; i < players[0].getSize(); i++)
//	{
//		Card temp = players[0].getTop();
//		cout << temp.getSuit() << "|" << temp.getValue() << endl;
//	}
	
	play(players);
	
}

int main() 
{
	bool debug = true;
	cout << "Welcome to the War Simulator!\n\n";
	
	int playerCount = 0;
	int deckCount = 0;
//	float turnTime = 0.0;
	
	if(debug)
	{
		playerCount = 3;
		deckCount = 1;
//		turnTime = 0.24;
	}
	else
	{
		cout << "Number of players: ";
		cin >> playerCount;
		
		cout << "Number of Decks: ";
		cin >> deckCount;
		
//		cout << "Seconds per turn (0.24): ";
//		cin >> turnTime;
	}
	
	start(deckCount, playerCount);
	
    return 0;
}
