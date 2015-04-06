/*====================================================
* Genetic Algorithm Homework 1
* Joel Ruiz II
* CSCI 4350 - Artificial Intelligence
* February 4, 2015
*
* Program Description:
* This Genetic Algorithm will attempt to fill a 32-bit string with all 1s by starting from an initial population of randomized 0s and 1s.
*
* ====================================================*/

#ifndef PARENT_H
#define PARENT_H


#include <stdlib.h>
#include <time.h>
#include "utils.h"


/**
* Parent
* The individual in a sample population.  We refer to them as a Parent, because they will eventually survive or be killed as one.  
* The population's master array id, genotypes, generation, fitness, and class settings are stored in this data structure. 
*/
class Parent
{

//-----------------------------------------------
private: //Member Variables
//-----------------------------------------------

	int m_iID;
	unsigned int m_iGene;
	int m_iGeneration;
	int m_iFitness;
	int m_iMaxBits;
	float m_flBitProbability;


//-----------------------------------------------
public: //Constructor/Destructor
//-----------------------------------------------

	//just incase we need a quicky
	Parent()
	{
		Parent(-1);
	}

	//initial population use this constructor
	Parent(int index)
	{
		setID(index);
		setGene(0);
		setGeneration(0);
		setFitness(0);
	}

	//children use this constructor
	Parent(int index, int maxbits, float bitProbability)
	{
		setID(index);
		setMaxBits(maxbits);
		setBitProbability(bitProbability);
		setGene(0);
		setGeneration(0);
		setFitness(0);
	}


//-----------------------------------------------
public: //Variable Accessors
//-----------------------------------------------

	bool	needsID()				{ return id() == -1; }
	int		id()					{ return m_iID; }
	void	setID(int id)			{ m_iID = id; }
	unsigned int gene()				{ return m_iGene; }
	void	setGene(unsigned int g)	{ m_iGene = g; }
	int		generation()			{ return m_iGeneration; }
	void	setGeneration(int g)	{ m_iGeneration = g; }
	int		fitness()				{ return m_iFitness; }
	void	setFitness(int f)		{ m_iFitness = f; }
	int		maxBits()				{ return m_iMaxBits; }
	float	bitProbability()		{ return m_flBitProbability; }
	void	setMaxBits(int maxBits) { m_iMaxBits = maxBits; }
	void	setBitProbability(float bitProbability) { m_flBitProbability = bitProbability; }


//-----------------------------------------------
public: //Class Methods
//-----------------------------------------------

	/**
	* Copy
	* Copy the information from another parent. 
	* This is used for when we do not use two-point crossover.
	* @param from - The parent we copy from
	* @return void
	*/
	void Copy(Parent *from)
	{
		this->setID(from->id());
		this->setFitness(from->fitness());
		this->setGene(from->gene());
		this->setBitProbability(from->bitProbability());
		this->setGeneration(from->generation());
		this->setMaxBits(from->maxBits());
	}
	

	/**
	* Print
	* Print the generation, genotype, and fitness of this parent with tabbing
	* @return void
	*/
	void print()
	{
		cout << generation() << "\t\t";
		Utils::printBits(gene(), maxBits());
		cout << "\t";
		cout << fitness();
		cout << endl;
	}

	/**
	* Generate
	* Parent genotypes will be generated by looping through each bit and for each bit if a random number is <= bit probability, is set to 1.
	* The genotype is on an unsigned integer, so we use bitwise OR and shifting to set individual bits.
	* Fitness will be calculated by how many 1s there are in the bit string.
	* @return void
	*/
	void Generate()
	{
		double randomNumber = 0;	//reusable random number
		int fitness = 0;			//fitness of our individual

		for (int i = 0; i<maxBits(); i++)
		{	
			//generate a random number between [0,1]
			randomNumber = ((double)Utils::random() / Utils::randomMax());	
			
			//genotype probabilty check
			if (randomNumber <= bitProbability())
			{
				//bitwise operation to set bit at position i to 1
				m_iGene |= (1 << i);

				//increase fitness for each genotype set to 1
				fitness++;		
			}
		}

		//Fitness is a ratio of how many 1s are set in our bit string from [0,1]
		setFitness(fitness);
	}

	
};


#endif //PARENT_H