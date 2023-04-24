#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Starship
{
public:
	struct Weapons
	{
		string weaponName;
		int power;
		float consumption;
	};
	unsigned int shipCount;
	string name;
	string shipClass;
	short length;
	int shield;
	float warp;
	int weaponCount;
	vector<Weapons> weapon;
	int shipPower;
	
	//THESE GETTERS ARE IRRELEVANT, LATE INTO THE CODING PROCESS I HAD TO MAKE THINGS PUBLIC BUT I WAS TOO LAZY TO CHANGE ALL THESE. IF IT AINT BROKE DONT FIX IT
	string GetName()
	{
		return name;
	}
	string getClass()
	{
		return shipClass;
	}
	short getLength()
	{
		return length;
	}
	int getShield()
	{
		return shield;
	}
	float getWarp()
	{
		return warp;
	}
	int GetWeaponCount()
	{
		return weaponCount;
	}
	


	Starship(string name, string shipClass, short length, int shield, float warp, int weaponCount, vector<Weapons> weapon)
	{
		this->name = name;
		this->shipClass = shipClass;
		this->length = length;
		this->shield = shield;
		this->warp = warp;
		this->weaponCount = weaponCount;
		this->weapon = weapon;
		shipPower = 0;
	}

};

	void GetDataFromFile(string filePath, vector<Starship>& shipList)
	{
		ifstream inFile(filePath, ios_base::binary);
		//Read the count first
		unsigned int count;
		inFile.read((char*)&count, sizeof(count));
		//shipCount = count; //Have a dedicated count for other functions
		//Read all the information for a single ship, create object with that information, and push it into a vector of ships
		for (unsigned int i = 0; i < count; i++)
		{
			//Name
			int length; // Get the length of the name
			inFile.read((char*)&length, sizeof(length));
			char* tempName = new char[length]; //Allocate char array with that size
			inFile.read(tempName, length); //Write the name to that array
			string name = tempName; //Copy over the name 
			delete[] tempName; //Delete the char array
			//Class
			inFile.read((char*)&length, sizeof(length));
			tempName = new char[length]; //Allocate char array with that size
			inFile.read(tempName, length); //Write the name to that array
			string shipClass = tempName; //Copy over the name 
			delete[] tempName; //Delete the char array
			//Length
			short shipLength;
			inFile.read((char*)&shipLength, sizeof(shipLength));
			//Shield
			int shield;
			inFile.read((char*)&shield, sizeof(shield));
			//Warp Speed
			float warp;
			inFile.read((char*)&warp, sizeof(warp));
			int weaponCount;
			inFile.read((char*)&weaponCount, sizeof(weaponCount));
			vector<Starship::Weapons> weapons; // Declare the weapons vector to store all the weapon info 
			if (weaponCount > 0) //If theres some weapons on the ship, get the name, power, and consumption
			{
				for (int i = 0; i < weaponCount; i++)
				{
					Starship::Weapons weapon; //Declare the weapon struct so I can use their variables
					//vector <Weapons> weapons;

					//Get Weapon name
					inFile.read((char*)&length, sizeof(length));
					tempName = new char[length];
					inFile.read(tempName, length);
					string weaponName = tempName;
					weapon.weaponName = weaponName; //Assign name to the weapon struct
					delete[] tempName;
					//Get weapon power
					int power;
					inFile.read((char*)&power, sizeof(power));
					weapon.power = power; //Assign power to the weapon struct
					//Get weapon consumption
					float consumption;
					inFile.read((char*)&consumption, sizeof(consumption));
					weapon.consumption = consumption; //Assign consumption to the weapon struct
					weapons.push_back(weapon); //push back the weapon struct into the weapons vector
		
				}
			}
			Starship ship(name, shipClass, shipLength, shield, warp, weaponCount, weapons); //Pass everything into the constructor to create the newly ship object
			shipList.push_back(ship); //Pass that newly made ship object into a vector of ships
		}
	}

	void PrintShip(vector<Starship>& shipList)
	{
		for (unsigned int i = 0; i < shipList.size(); i++)
		{
			cout << "Name: " << shipList[i].GetName() << endl;
			cout << "Class: " << shipList[i].getClass() << endl;
			cout << "Length: " << shipList[i].getLength() << endl;
			cout << "Shield capacity: " << shipList[i].getShield() << endl;
			cout << "Maximum Warp: " << shipList[i].getWarp() << endl;
			cout << "Armaments: " << endl;
			if (shipList[i].GetWeaponCount() == 0)
			{
				cout << "Unarmed" << endl;
				cout << " " << endl;
			}
			else
			{
				for (int j = 0; j < shipList[i].GetWeaponCount(); j++)
				{
					cout << shipList.at(i).weapon[j].weaponName << ", " << shipList.at(i).weapon[j].power << ", " << shipList.at(i).weapon[j].consumption << endl;
					shipList.at(i).shipPower = shipList.at(i).shipPower + shipList.at(i).weapon[j].power;
				}
				cout << "Total firepower: " << shipList.at(i).shipPower << endl;
				cout << " " << endl;
			}
		}
	}

	void StrongestWep(vector<Starship>& shipList)
	{
		unsigned int counter = 0;
		int maxPower = 0;
		int powerIterator = 0;
		int maxPowerIndex = 0;
		while (counter < shipList.size())
		{
			for (int i = 0; i < shipList[counter].GetWeaponCount(); i++)
			{
				powerIterator = shipList.at(counter).weapon[i].power;
				if (powerIterator > maxPower)
				{
					maxPower = powerIterator;
					maxPowerIndex = counter;
				}
			}
			counter = counter + 1;
		}
		cout << "Name: " << shipList[maxPowerIndex].GetName() << endl;
		cout << "Class: " << shipList[maxPowerIndex].getClass() << endl;
		cout << "Length: " << shipList[maxPowerIndex].getLength() << endl;
		cout << "Shield capacity: " << shipList[maxPowerIndex].getShield() << endl;
		cout << "Maximum Warp: " << shipList[maxPowerIndex].getWarp() << endl;
		cout << "Armaments: " << endl;
		for (int j = 0; j < shipList[maxPowerIndex].GetWeaponCount(); j++)
		{
			cout << shipList.at(maxPowerIndex).weapon[j].weaponName << ", " << shipList.at(maxPowerIndex).weapon[j].power << ", " << shipList.at(maxPowerIndex).weapon[j].consumption << endl;
			shipList.at(maxPowerIndex).shipPower = shipList.at(maxPowerIndex).shipPower + shipList.at(maxPowerIndex).weapon[j].power;
		}
		cout << "Total firepower: " << shipList.at(maxPowerIndex).shipPower << endl;
		cout << " " << endl;
	}

	void StrongestShip(vector<Starship>& shipList) // Print out the ship with the highest firepower 
	{
		int totalPower = 0;
		int totalPowerBuffer = 0;
		int strongestIndex = 0;
		for (unsigned int i = 0; i < shipList.size(); i++)
		{
			totalPower = 0;
			for (int j = 0; j < shipList.at(i).GetWeaponCount(); j++)
			{
				totalPower = shipList.at(i).weapon[j].power + totalPower;
			}
			if (totalPower > totalPowerBuffer)
			{
				totalPowerBuffer = totalPower;
				strongestIndex = i;
			}
		}
		cout << "Name: " << shipList[strongestIndex].GetName() << endl;
		cout << "Class: " << shipList[strongestIndex].getClass() << endl;
		cout << "Length: " << shipList[strongestIndex].getLength() << endl;
		cout << "Shield capacity: " << shipList[strongestIndex].getShield() << endl;
		cout << "Maximum Warp: " << shipList[strongestIndex].getWarp() << endl;
		cout << "Armaments: " << endl;
		for (int k = 0; k < shipList[strongestIndex].GetWeaponCount(); k++)
		{
			cout << shipList.at(strongestIndex).weapon[k].weaponName << ", " << shipList.at(strongestIndex).weapon[k].power << ", " << shipList.at(strongestIndex).weapon[k].consumption << endl;
			shipList.at(strongestIndex).shipPower = shipList.at(strongestIndex).shipPower + shipList.at(strongestIndex).weapon[k].power;
		}
		cout << "Total firepower: " << shipList.at(strongestIndex).shipPower << endl;
		cout << " " << endl;
	}

	void WeakestShip(vector<Starship>& shipList) //Print out the weakest ship, excluding the ones with no weapons
	{
		int totalPower = 0;
		int totalPowerBuffer = 10000;
		int weakestIndex = 0;
		for (unsigned int i = 0; i < shipList.size(); i++)
		{
			totalPower = 0;
			for (int j = 0; j < shipList.at(i).GetWeaponCount(); j++)
			{
				totalPower = shipList.at(i).weapon[j].power + totalPower;
			}
			if (totalPower < totalPowerBuffer && totalPower != 0)
			{
				totalPowerBuffer = totalPower;
				weakestIndex = i;
			}
		}
		cout << "Name: " << shipList[weakestIndex].GetName() << endl;
		cout << "Class: " << shipList[weakestIndex].getClass() << endl;
		cout << "Length: " << shipList[weakestIndex].getLength() << endl;
		cout << "Shield capacity: " << shipList[weakestIndex].getShield() << endl;
		cout << "Maximum Warp: " << shipList[weakestIndex].getWarp() << endl;
		cout << "Armaments: " << endl;
		for (int k = 0; k < shipList[weakestIndex].GetWeaponCount(); k++)
		{
			cout << shipList.at(weakestIndex).weapon[k].weaponName << ", " << shipList.at(weakestIndex).weapon[k].power << ", " << shipList.at(weakestIndex).weapon[k].consumption << endl;
			shipList.at(weakestIndex).shipPower = shipList.at(weakestIndex).shipPower + shipList.at(weakestIndex).weapon[k].power;
		}
		cout << "Total firepower: " << shipList.at(weakestIndex).shipPower << endl;
		cout << " " << endl;
	}

	void UnarmedShip(vector<Starship>& shipList) //Print all the unarmed ships
	{
		for (unsigned int i = 0; i < shipList.size(); i++)
		{
			if (shipList[i].GetWeaponCount() == 0)
			{
				cout << "Name: " << shipList[i].GetName() << endl;
				cout << "Class: " << shipList[i].getClass() << endl;
				cout << "Length: " << shipList[i].getLength() << endl;
				cout << "Shield capacity: " << shipList[i].getShield() << endl;
				cout << "Maximum Warp: " << shipList[i].getWarp() << endl;
				cout << "Armaments: " << endl;
				cout << "Unarmed" << endl;
				cout << " " << endl;
			}
		}
	}

int main()
{
	vector<Starship> shipList;

	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	if (option == 1)
	{
		GetDataFromFile("friendlyships.shp", shipList);
	}
	if (option == 2)
	{
		GetDataFromFile("enemyships.shp", shipList);
	}
	if (option == 3)
	{
		GetDataFromFile("friendlyships.shp", shipList);
		GetDataFromFile("enemyships.shp", shipList);
	}

	/* Load files here */

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	/* Work your magic here */
	if (option == 1)
	{
		PrintShip(shipList);
	}
	if (option == 2)
	{
		StrongestWep(shipList);
	}
	if (option == 3)
	{
		StrongestShip(shipList);
	}
	if (option == 4)
	{
		WeakestShip(shipList);
	}
	if (option == 5)
	{
		UnarmedShip(shipList);
	}
	return 0;
}
