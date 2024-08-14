/*
Carrie Yu

Subclass of ArrayBag that stores Character objects
Tiziana Ligorio
*/

#include "Tavern.hpp"
#include <cmath> //for std::round(), which has better consistency than round()

/**
    Default constructor.
    Default-initializes all private members. 
*/
Tavern:: Tavern(): ArrayBag<Character>(){
    total_characterLevels = 0;
    count_characterEnemies = 0;
}

/** @param:   A const reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to the tavern (i.e. items_), false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count 
              if the character is an enemy.
**/
bool Tavern:: enterTavern(const Character& character_enterTavern){

    //if the character entering the tavern is an enemy, then increment the enemy count by 1
    if(character_enterTavern.isEnemy() == true){
        count_characterEnemies ++;
    }

    //if the character is able to be added to the tavern, increment the current level by the designated character level
    if(add(character_enterTavern)){ 
        total_characterLevels += character_enterTavern.getLevel();
        return true;
    }
    return false;
    
}

/** @param:   A const reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from the tavern (i.e. items_), false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count
              if the character is an enemy.
**/
bool Tavern:: exitTavern(const Character& character_leftTavern){

    //if the character leaving the tavern is an enemy, then decrement the enemy count by 1
    if(character_leftTavern.isEnemy() == true){
        count_characterEnemies --;
    }

    //if the character is able to leave the tavern, decrement the designated level amount from the current level
    if(remove(character_leftTavern) == true){ 
        total_characterLevels -= character_leftTavern.getLevel();
        return true;
    }
    return false;

}

/** 
    @return:  The integer level count of all the characters currently in the Tavern
**/
int Tavern:: getLevelSum() const{
    return total_characterLevels;
}

/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Computes the average level of the Tavern rounded to the NEAREST integer.
**/
int Tavern:: calculateAvgLevel() const{

    //convert to doubles for accurate rounding purposes
    double level_sum = getLevelSum();
    double numOf_characters = getCurrentSize();

    double avg_levels = std::round(level_sum/numOf_characters);

    return avg_levels;

}

/** 
    @return:  The integer enemy count of the Tavern
**/
int Tavern:: getEnemyCount() const{
    return count_characterEnemies; 
}

/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Computes the enemy percentage of the Tavern rounded up to 2 decimal places.
**/
double Tavern:: calculateEnemyPercentage() const{

    //what percentage of characters are ENEMIES

    //convert to doubles for accurate rounding purposes
    double enemy_count = getEnemyCount();
    double numOf_characters = getCurrentSize();

    double enemy_decimal = (enemy_count*100/numOf_characters*100); //hundredths place
    double enemy_percentage = std::round(enemy_decimal)/100; //convert decimal to percentage

    return enemy_percentage;

}



/** 
    @param:   A const reference to a string representing a character Race with value in 
              ["NONE", "HUMAN", "ELF", "DWARF", "LIZARD", "UNDEAD"]
    @return:  An integer tally of the number of characters in the Tavern of the given race. 
              If the argument string does not match one of the expected race values, 
              the tally is zero. NOTE: no pre-processing of the input string necessary, only uppercase input will match.
**/
int Tavern:: tallyRace(const std::string& character_race){
    
    int count_tallies = 0; //stores the frequnecy of each character race

    for(int i = 0; i < getCurrentSize(); i++){
        if(character_race == items_[i].getRace()){ //if the param race matches a race from the Character class,
            count_tallies++; //then increment the count for that specific race by 1
        }
    }
    return count_tallies;

}


/**
@post:      Outputs a report of the characters currently in the tavern in the form:
            "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n"
            Note that the average level should be rounded to the NEAREST integer, and the enemy percentage should be rounded to 2 decimal places.

            Example output: 
            Humans: 3
            Elves: 5
            Dwarves: 8
            Lizards: 6
            Undead: 0

            The average level is: 7
            46.67% are enemies.
*/
void Tavern:: tavernReport(){

    std:: cout << "Humans: " << tallyRace("HUMAN") 
               << "\nElves: " << tallyRace("ELF") 
               << "\nDwarves: " << tallyRace("DWARF") 
               << "\nLizards: " << tallyRace("LIZARD")
               << "\nUndead: " << tallyRace("UNDEAD") 
               << "\n\nThe average level is: " << calculateAvgLevel() 
               << "\n" << calculateEnemyPercentage() << "% are enemies.\n" << std:: endl;
               
}