#include "seeplusia.hpp"
#include "mover.hpp"

int applesLeft = 20, nCrystalsFound = 0;
string gameState = "Running";			  					// gameState to imply that the game is currently Running
string currentState = "Enchanted Forest"; 						// Starting position on game map
bool MarshCrystal = true;				  				// For crystal at Marsh of the Undead
bool EistenCrystal = true;				  				// For crystal at Eisten Tunnel
bool WerewolfCrystal = true;			  					// For crystal at Werewolf's Hill
bool SwampsCrystal = true;				  				// For crystal at Swamps of Despair

// Function to allow player to move only in the specified directions
void makeMove(string direction)
{
	if (direction == "East" && applesLeft > 0) 					// When Right Arrow is pressed
	{
		if (currentState == "Enchanted Forest" && applesLeft >= 1) 		// Enchanted Forest ---> Sands of Quick ---> Game Lost!
		{
			currentState = "Sands of Quick";
			applesLeft--;
			cout << "Enchanted Forest ---> Sands of Quick ---> You sank in sand and died!" << endl;
			moveEast();							// This function is called only if warrior needs to be moved to the right
			gameState = "Lost"; 						// gameState when the game is Lost
		}

		else if (currentState == "Wampire Cove" && applesLeft >= 1) 		// Wampire Cove ---> Marsh of Undead, crystal found
		{
			currentState = "Marsh of Undead";
			applesLeft -= 1;
			cout << "Wampire Cove ---> Marsh of Undead" << endl;
			moveEast();
			gameState = "Running";
			if (MarshCrystal == true) 			// Since there is a crystal here at the Marsh, we want to make sure the crystal is only collected once.
			{
				nCrystalsFound++;	  				// To increment number of crystals found
				MarshCrystal = false; 		// It is changed to false so that once marsh_d != true, the condition is skipped and no crystal is collected.
			}
		}

		else if (currentState == "Swamps of Despair" && applesLeft >= 1) 	// Swamps of Despair ---> Wampire Cove
		{
			currentState = "Wampire Cove";
			applesLeft -= 1;
			cout << "Swamps of Despair ---> Wampire Cove" << endl;
			gameState = "Running";
			moveEast();
		}

		else if (currentState == "Elvin Waterfall" && applesLeft >= 2) 		// Elvin Waterfall ---> Werewolf Hill, crystal found
		{
			currentState = "Werewolf Hill";
			applesLeft -= 2;
			cout << "Elvin Waterfall ---> Werewolf Hill" << endl;
			gameState = "Running";
			moveEast();
			if (WerewolfCrystal == true)
			{
				nCrystalsFound++;					// A crystal was collected
				WerewolfCrystal = false; 
			}
		}

		else if (currentState == "Eisten Tunnel" && applesLeft >= 2) 		// Eisten Tunnel ---> Elvin Waterfall
		{
			currentState = "Elvin Waterfall";
			applesLeft -= 2;
			cout << "Eisten Tunnel ---> Elvin Waterfall" << endl;
			gameState = "Running";
			moveEast();
		}

		else 						/* A condition to make sure that the player doesn't go in a direction where there are no arrows on the map/
								player can't cross the path if he has lesser number of apples.*/
		{
			applesLeft -= 1;
			cout << "Invalid Move" << endl;
		}
	}

	else if (direction == "West" && applesLeft > 0) 				// When Left Arrow is pressed
	{
		if (currentState == "Bridge of Death" && applesLeft >= 5 && nCrystalsFound == 4) 	// Bridge of Death ---> Wizard's Castle ---> Game Won!
		{
			currentState = "Wizard's Castle";
			applesLeft -= 5;
			cout << "Bridge of Death ---> Wizard's Castle ---> Game Won!" << endl;
			moveWest();		   					// This function is called only if warrior needs to be moved to the left
			gameState = "Won"; 						// gameState when the game is Won
		}

		else if (currentState == "Bridge of Death" && (applesLeft < 5 || nCrystalsFound != 4)) 	// Bridge of Death ---> Wizard's Castle ---> Game Lost!
		{
			currentState = "Wizard's Castle";
			cout << "Bridge of Death ---> Wizard's Castle ---> You have <5 apples and/or <4 crystals" << endl;
			gameState = "Running";
		}

		else if (currentState == "Wampire Cove" && applesLeft >= 1) 		// Wampire Cove ---> Swamps of Despair, crystal found
		{
			currentState = "Swamps of Despair";
			applesLeft -= 1;
			cout << "Wampire Cove ---> Swamps of Despair" << endl;
			moveWest();
			gameState = "Running";
			if (SwampsCrystal == true)
			{
				nCrystalsFound++;					// A crystal was collected
				SwampsCrystal = false; 
			}
		}

		else if (currentState == "Apples Orchard" && applesLeft >= 1) 		// Apples Orchard ---> Werewolf Hill, crystal found
		{
			currentState = "Werewolf Hill";
			applesLeft -= 1;
			cout << "Apples Orchard ---> Werewolf Hill" << endl;
			moveWest();
			gameState = "Running";
			if (WerewolfCrystal == true)
			{
				nCrystalsFound++;					// A crystal was collected
				WerewolfCrystal = false; 
			}
		}

		else if (currentState == "Werewolf Hill" && applesLeft >= 2) 		// Werewolf Hill ---> Elvin Waterfall
		{
			currentState = "Elvin Waterfall";
			applesLeft -= 2;
			cout << "Werewolf Hill ---> Elvin Waterfall" << endl;
			gameState = "Running";
			moveWest();
		}

		else if (currentState == "Elvin Waterfall" && applesLeft >= 2) 		// Elvin Waterfall ---> Eisten Tunnel, crytsal found
		{
			currentState = "Eisten Tunnel";
			applesLeft -= 2;
			cout << "Elvin Waterfall ---> Eisten Tunnel (Make sure you have atleast 10 apples and 3 crystals to go North!)" << endl;
			gameState = "Running";
			moveWest();
			if (EistenCrystal == true)
			{
				nCrystalsFound++;					// A crystal was collected
				EistenCrystal = false; 
			}
		}

		else if (currentState == "Marsh of Undead" && applesLeft >= 1) 		// Marsh of Undead ---> Wampire Cove
		{
			currentState = "Wampire Cove";
			applesLeft -= 1;
			cout << "Marsh of Undead ---> Wampire Cove" << endl;
			moveWest();
			gameState = "Running";
		}

		else
		{
			applesLeft -= 1;
			cout << "Invalid Move" << endl;
		}
	}

	else if (direction == "North" && applesLeft > 0) 				// When Up Arrow is pressed
	{
		if (currentState == "Wampire Cove" && applesLeft >= 3) 			// Wampire Cove ---> Enchanted Forest
		{
			currentState = "Enchanted Forest";
			applesLeft -= 3;
			cout << "Wampire Cove ---> Enchanted Forest" << endl;
			moveNorth();
			gameState = "Running";
		}

		else if (currentState == "Werewolf Hill" && applesLeft >= 3) 		// Werewolf Hill --> Wampire Cove
		{
			currentState = "Wampire Cove";
			applesLeft -= 3;
			cout << "Werewolf Hill --> Wampire Cove" << endl;
			moveNorth();
			gameState = "Running";
		}

		else if (currentState == "Swamps of Despair" && applesLeft >= 1) 	// Swamps of Despair --> Bridge of Death
		{
			currentState = "Bridge of Death";
			applesLeft -= 1;
			cout << "Swamps of Despair --> Bridge of Death" << endl;
			moveNorth();
			gameState = "Running";
		}

		else if (currentState == "Eisten Tunnel" && applesLeft >= 10 && nCrystalsFound >= 3) 	// Eisten Tunnel --> Wizard's Castle ---> Game Won!
		{
			currentState = "Wizard's Castle";
			applesLeft -= 10;
			cout << "Eisten Tunnel --> Wizard's Castle ---> Game Won!" << endl;
			moveNorth();
			moveNorth();
			gameState = "Won";
		}

		else if (currentState == "Eisten Tunnel" && (applesLeft < 10 || nCrystalsFound < 3)) 	// Eisten Tunnel --> Wizard's Castle ---> Game Lost!
		{
			currentState = "Wizard's Castle";
			cout << "You don't have 10 apples and/or 3 crystals to cross" << endl;
			gameState = "Running";
		}

		else
		{
			applesLeft -= 1;
			cout << "Invalid Move" << endl;
		}
	}

	else if (direction == "South" && apples > 0) // When Down Arrow is pressed
	{
		if (currentState == "Enchanted Forest" && applesLeft >= 3) 				// Enchanted Forest ---> Wampire Cove
		{
			currentState = "Wampire Cove";
			applesLeft -= 3;
			cout << "Enchanted Forest ---> Wampire Cove" << endl;
			moveSouth();
			gameState = "Running";
		}

		else if (currentState == "Wampire Cove" && applesLeft >= 3) 				// Wampire Cove ---> Werewolf Hill, crystal found
		{

			currentState = "Werewolf Hill";
			applesLeft -= 3;
			cout << "Wampire Cove ---> Werewolf Hill" << endl;
			moveSouth();
			gameState = "Running";
			if (WerewolfCrystal == true)
			{
				nCrystalsFound++;							// A crystal was collected
				WerewolfCrystal = false; 
			}
		}

		else if (currentState == "Marsh of Undead" && applesLeft >= 1) 				// Marsh of Undead ---> Apples Orchard
		{

			currentState = "Apples Orchard";
			applesLeft += 5;
			cout << "Marsh of Undead ---> Apples Orchard";
			moveSouth();
			gameState = "Running";
		}

		else
		{
			applesLeft -= 1;
			cout << "Invalid Move" << endl;
		}
	}

	else if (applesLeft <= 0) 									// If player runs out of apples, he dies of starvation
	{
		cout << "You ran out of apples and died of starvation ---> Game Lost!" << endl;
		gameState = "Lost";
	}
}
