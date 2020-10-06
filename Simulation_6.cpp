//
//  main.cpp
//  rover_domain
//
//  Created by ak on 10/11/18.
//  Copyright © 2018 ak. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <cmath>
#include <math.h>
#include <random>
#include <assert.h>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

#define PI 3.14159265

vector<double> three_0 = {0,0,0};
vector<double> three_1 = {2,2,4};
vector<double> three_2 = {3,9,8};
vector<double> three_3 = {1,4,9};
vector<double> three_4 = {15,6,1};

vector<double> four_0 = {0,0,0,0};
vector<double> four_1 = {2,2,4,1};
vector<double> four_2 = {15,6,1,5};
vector<double> four_3 = {18,18,4,1};
vector<double> four_4 = {1,4,14,5};


/*************************
 Neural Network
 ************************/

struct connect{
    double weight;
};

/********************************************
 Fucntion generates random number
 *********************************************/

static double random_global(double a) { return a* (rand() / double(RAND_MAX)); }

// This is for each Neuron
class Neuron;
typedef vector<Neuron> Layer;

class Neuron{
public:
    Neuron(unsigned numOutputs, unsigned myIndex,int numNN);
    vector<connect> z_outputWeights;
    static double randomWeight(void) { return rand() / double(RAND_MAX); }
    unsigned z_myIndex;
    double z_outputVal;
    void setOutputVal(double val) { z_outputVal = val; }
    double getOutputVal(void) const { return z_outputVal; }
    void feedForward(const Layer prevLayer);
    double transferFunction(double x);
    
};

/********************************************
 //This creates connection with neurons.weight is weight of each connection
 *********************************************/
Neuron::Neuron(unsigned numOutputs, unsigned myIndex,int number){
    for (unsigned c = 0; c < numOutputs; ++c) {
        z_outputWeights.push_back(connect());
        double Min = 0.5;
        double Max = 1.0;
        number = rand()%9;
        
        // Old way check
        Min = -1.0;
        Max = 1.0;
        double random_number = (((double) rand() / RAND_MAX) * (Max-Min)) +Min;
        //        FILE* p_weights_neuron;
        //        p_weights_neuron = fopen("neuron", "a");
        //        fprintf(p_weights_neuron, "%d \t %f \t",number, random_number);
        //        fclose(p_weights_neuron);
        
        z_outputWeights.back().weight = (random_number);
        // ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
    }
    z_myIndex = myIndex;
}

/********************************************
 //Function for activation function. We currently have 3 but using tanh function
 *********************************************/
double Neuron::transferFunction(double x){
    int case_to_use = 3;
    switch (case_to_use) {
        case 1:
            //return sin((x*(180/PI)));
            //return cos(x*(180/PI));
            
            break;
        case 2:
            //Dont use this case
            return tanh(x);
            //return 1/(1+exp(x));
            break;
        case 3:
            return x/(1+abs(x));
            break;
            
        default:
            break;
    }
    
    return tanh(x);
    
}

/********************************************
 // In this function weight*value is performed.
 //In addition weight*value is summed up
 //After that passed through activation function
 *********************************************/

void Neuron::feedForward(const Layer prevLayer){
    double sum = 0.0;
    
    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        //        cout << prevLayer[n].getOutputVal() * prevLayer[n].z_outputWeights[z_myIndex].weight<<endl;
        //        cout << prevLayer[n].z_outputWeights[z_myIndex].weight<<endl;
        //        cout << prevLayer[n].getOutputVal()<<endl;
        sum += prevLayer[n].getOutputVal() * prevLayer[n].z_outputWeights[z_myIndex].weight;
        //        cout<<"This is sum value"<<sum<<endl;
    }
    
    
    z_outputVal = Neuron::transferFunction(sum);
    
    //    cout<<z_outputVal<<endl;
}

/********************************************
 //This is single neural network
 *********************************************/
class Net{
public:
    Net(vector<unsigned> topology,int numNN,int number);
    void feedForward(vector<double> inputVals);
    vector<Layer> z_layer;
    vector<double> outputvaluesNN;
    double backProp();
    double z_error;
    double z_error_temp;
    vector<double> z_error_vector;
    void mutate();
    vector<double> temp_inputs;
    vector<double> temp_targets;
    
    //coordinates
    vector<double> x_coordinates;
    vector<double> y_coordinates;
    vector<double> z_coordinates;

    //coordinates using functions
    vector<double> x_coordinates_unicycle;
    vector<double> y_coordinates_unicycle;
    vector<double> z_coordinates_unicycle;

    vector<double> theta_unicycle;
    vector<double> omega_unicycle;
    
    double velocity_left, velocity_right;

    vector<double> target_distance;//Distance to target
    vector<double> target_distance_1; //Distance to target 1
    double shortest_target_distance; // Shortest distance to target
    double shortest_target_distance_1; //Second location of target
    
    double global_target_1,global_target_2,global_obstacle,global_agent,global_summation_hitting;
    double difference_target_1,difference_target_2,difference_obstacle,difference_agent,difference_summation_hitting;
    
    vector<vector<double>> obstacle_distance; //Saves all obstacle distances
    double hitting_obstacle;// Hitting of obstacle all of them
    
    vector<vector<double>> right_rover; // Right rover distance values
    vector<vector<double>> left_rover; //left rover distance values
    vector<vector<double>> other_rover_paths;//saves other rover values
    double summation_hitting; // Used for ea
    double hitting_agents_summation;
    
    
    double formation_of_team; //global formation
    double difference_formation;//difference in formation
    
    vector<double> hitting_values; // Instead of right and left lets combine both of them
    vector<double> hitting_right_rover; // Hitting right rover
    vector<double> hitting_left_rover; // Hitting left rover
    
    //FOR CCEA
    vector<double> fintess_values; // This is fitness from simulation
    vector<double> normalized_fitness_values; // This is fitness from over all fitnesses
    vector<double> normalized_fitness_topsis; // This is fitness for normalization of topsis
    vector<int> dominating_them;
    int front_number;bool in_front;int number_in_front;bool remove_me;double crowding_distance;int getting_dominated_by;
    int team_number;
    
    int reference_line;
    
    void swap_function();
    
    double summation_fitness_value;
    int rank;
    bool hall_of_fame;
    double distance_to_hall_of_fame;
    bool good_for_next_generation;
    vector<double> normalized_fitness_values_hof;
    double euclidean_best;
    double eculidean_worst;
    double performance_score;
    
};

/********************************************
 //Here we are creating neural network with given topology
 //Topology is given in main function
 *********************************************/
Net::Net(vector<unsigned> topology,int numNN,int number){
    
    for(int  numLayers = 0; numLayers<topology.size(); numLayers++){
        //unsigned numOutputs = numLayers == topology.size() - 1 ? 0 : topology[numLayers + 1];
        
        unsigned numOutputs;
        if (numLayers == topology.size()-1) {
            numOutputs=0;
        }else{
            numOutputs= topology[numLayers+1];
        }
        
        if(numOutputs>30){
            cout<<"Stop it number outputs coming out"<<numOutputs<<endl;
            exit(10);
        }
        
        z_layer.push_back(Layer());
        
        for(int numNeurons = 0; numNeurons <= topology[numLayers]; numNeurons++){
            //cout<<"This is neuron number:"<<numNeurons<<endl;
            z_layer.back().push_back(Neuron(numOutputs, numNeurons,number));
        }
        z_layer.back().back().setOutputVal(1.0);
    }
}


void Net::swap_function(){
    vector<double>().swap(fintess_values);
    vector<double>().swap(normalized_fitness_values);
    vector<int>().swap(dominating_them);
    vector<double>().swap(hitting_values);
    vector<double>().swap(hitting_right_rover);
    vector<double>().swap(hitting_left_rover);
    vector<double>().swap(x_coordinates);
    vector<double>().swap(y_coordinates);
    vector<vector<double>>().swap(right_rover);
    vector<vector<double>>().swap(left_rover);
    vector<vector<double>>().swap(obstacle_distance);
    vector<double>().swap(target_distance);
    vector<double>().swap(target_distance_1);
    vector<vector<double>>().swap(other_rover_paths);
    vector<double>().swap(x_coordinates_unicycle);
    vector<double>().swap(y_coordinates_unicycle);
    
}

/********************************************
 //This function is used in evolutionary algorithm
 //We are changing weights of all connections in the following
 *********************************************/
void Net::mutate(){
    /*
     //popVector[temp].z_layer[temp][temp].z_outputWeights[temp].weight
     */
    for (int l =0 ; l < z_layer.size(); l++) {
        for (int n =0 ; n< z_layer.at(l).size(); n++) {
            for (int z=0 ; z< z_layer.at(l).at(n).z_outputWeights.size(); z++) {
                //                z_layer.at(l).at(n).z_outputWeights.at(z).weight = (random_global(.5)-random_global(.5));
                //                z_layer.at(l).at(n).z_outputWeights.at(z).weight += ((((double) rand() / RAND_MAX) * 2) - 1.0);
                z_layer.at(l).at(n).z_outputWeights.at(z).weight += (random_global(.05)-random_global(.05));
            }
        }
    }
}

/********************************************
 //Neuron feedforward does only for one neuron. Here we are doing for entire neural network
 //Each neuron feedforward is called from this function
 *********************************************/
void Net::feedForward(vector<double> inputVals){
    // cout<<inputVals.size()<<endl;

    assert(inputVals.size() == z_layer[0].size()-1);
    for (unsigned i=0; i<inputVals.size(); ++i) {
        z_layer[0][i].setOutputVal(inputVals[i]);
    }
    for (unsigned layerNum = 1; layerNum < z_layer.size(); ++layerNum) {
        Layer &prevLayer = z_layer[layerNum - 1];
        for (unsigned n = 0; n < z_layer[layerNum].size() - 1; ++n) {
            z_layer[layerNum][n].feedForward(prevLayer);
        }
    }
    temp_inputs.clear();
    Layer &outputLayer = z_layer.back();
    z_error_temp = 0.0;
    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        //cout<<"This is value from outputlayer.getourputvalue:::::"<<outputLayer[n].getOutputVal()<<endl;
        //double delta = temp_targets[n] - outputLayer[n].getOutputVal();
        //cout<<"This is delta value::"<<delta;
        //z_error_temp += delta * delta;
        outputvaluesNN.push_back(outputLayer[n].getOutputVal());
    }
    
    
    
}

/********************************************
 We are not using this function. This is just for my testing to print out error
 *********************************************/
double Net::backProp(){
    z_error = 0.0;
    for (int temp = 0; temp< z_error_vector.size(); temp++) {
        //cout<<"This is z_error_vector"<<temp<<" value::"<< z_error_vector[temp]<<endl;
        z_error += z_error_vector[temp];
    }
    //    cout<<"This is z_error::"<<z_error<<endl;
    return z_error;
}


/**************************
 New Rover
 **************************/

class new_rover{
public:
    double x_location_new,y_location_new,z_location_new;
    double target_x,target_y,target_z;
    double target_x_1,target_y_1,target_z_1;
    double length_of_rover;
    vector<double> sensor;
    void create_nn(int numNN, vector<unsigned> topology);
    vector<Net> new_network;
    void sense_new_rover(double x,double y, double z);
    void sense_new_target(double x, double y, double z);
    void sense_new_ob(double x, double y, double z);
    void sense_new_target_1(double x, double y, double z);
    int quad_value(double difference_x, double difference_y,double difference_z);
    void reset_sensor_value();
    void set_sensor_zero();
};


// variables used: indiNet -- object to Net
void new_rover::create_nn(int numNN,vector<unsigned> topology){
    for (int populationNum = 0 ; populationNum<numNN; populationNum++) {
        //cout<<"This is neural network:"<<populationNum<<endl;
        Net singleNetwork(topology,numNN,populationNum);
        new_network.push_back(singleNetwork);
    }
}

void new_rover::reset_sensor_value(){
    sensor.clear();
    if (sensor.size()!= 16) {
        for (int i=0; i<16; i++) {
            sensor.push_back(0.0);
        }
    }
}

void new_rover::set_sensor_zero(){
    for (int i=0; i<16; i++) {
        sensor.push_back(0.0);
    }
}

int new_rover::quad_value(double difference_x, double difference_y,double difference_z){
    if (difference_x >= 0 && difference_y  >= 0) {
        if (difference_z >=0) {
            return 1;
        }
        
    }else if (difference_x >= 0 && difference_y < 0){
        return 4;
    }else if (difference_x <= 0 && difference_y >0){
        return 2;
    }else if(difference_x <= 0 && difference_y <0){
        return 3;
    }
    
    return 2;
}

void new_rover::sense_new_rover(double x, double y, double z){
    double difference_x = x-x_location_new;
    double difference_y = y-y_location_new;
    double difference_z = z-z_location_new;
    double distance_rover = sqrt(pow(difference_x, 2)+pow(difference_y, 2)+pow(difference_y, 2));
    int quad = quad_value(difference_x, difference_y, difference_z);
    if (quad == 1) {
        sensor.at(0) += distance_rover;
    }else if (quad == 2){
        sensor.at(4) += distance_rover;
    }else if (quad == 3){
        sensor.at(8) += distance_rover;
    }else{
        sensor.at(12) +=distance_rover;
    }
    
}

void new_rover::sense_new_target(double x, double y, double z){
    double difference_x = x - x_location_new;
    double difference_y = y - y_location_new;
    double difference_z = z - z_location_new;
    double distance_rover = sqrt(pow(difference_x, 2)+pow(difference_y, 2)+pow(difference_z, 2));
    int quad = quad_value(difference_x, difference_y, difference_z);
    if (quad == 1) {
        sensor.at(1) += distance_rover;
    }else if (quad == 2){
        sensor.at(5) += distance_rover;
    }else if (quad == 3){
        sensor.at(9) += distance_rover;
    }else{
        sensor.at(13) +=distance_rover;
    }
}

void new_rover::sense_new_ob(double x, double y , double z){
    double difference_x = x-x_location_new;
    double difference_y = y-y_location_new;
    double difference_z = z - z_location_new;
    double distance_rover = sqrt(pow(difference_x, 2)+pow(difference_y, 2)+pow(difference_z, 2));
    int quad = quad_value(difference_x, difference_y, difference_z);
    if (quad == 1) {
        sensor.at(2) += distance_rover;
    }else if (quad == 2){
        sensor.at(6) += distance_rover;
    }else if (quad == 3){
        sensor.at(10) += distance_rover;
    }else{
        sensor.at(14) +=distance_rover;
    }
}

void new_rover::sense_new_target_1(double x, double y , double z){
    double difference_x = x-x_location_new;
    double difference_y = y-y_location_new;
    double difference_z = z - z_location_new;
    double distance_rover = sqrt(pow(difference_x, 2)+pow(difference_y, 2)+pow(difference_z, 2));
    int quad = quad_value(difference_x, difference_y, difference_z);
    if (quad == 1) {
        sensor.at(3) += distance_rover;
    }else if (quad == 2){
        sensor.at(7) += distance_rover;
    }else if (quad == 3){
        sensor.at(11) += distance_rover;
    }else{
        sensor.at(15) +=distance_rover;
    }
}


/********************************************************
 Population of each team
 *******************************************************/
class population{
public:
    population(int number_of_rover, int number_of_routes);
    vector<new_rover> teamRover;
    vector<vector<int>> path_numbers;
    
};

population::population(int number_of_rover, int number_of_routes){
    //This is for neural network
    vector<unsigned> topology;
    topology.clear();
    topology.push_back(16);
    topology.push_back(7);
    topology.push_back(3);
    new_rover a;
    
    //This created neural network on the rover
    for (int number = 0 ; number < number_of_rover; number++) {
        teamRover.push_back(a);
        teamRover.at(number).create_nn(number_of_routes, topology);
    }
    
}

/********************************************************
 This function is to calculate scalarization of neural network
 ********************************************************/

void scalarization(vector<new_rover> teamRover,int rover){
    double min = 9999.99;
    double max = -9999999.99;
    for (int sense = 0; sense < teamRover.at(rover).sensor.size(); sense++) {
        if (teamRover.at(rover).sensor.at(sense) < min) {
            min = teamRover.at(rover).sensor.at(sense);
        }
        
        if (teamRover.at(rover).sensor.at(sense) > max) {
            max = teamRover.at(rover).sensor.at(sense);
        }
    }
    
    for (int sense = 0; sense < teamRover.at(rover).sensor.size(); sense++) {
        double temp = teamRover.at(rover).sensor.at(sense);
        teamRover.at(rover).sensor.at(sense) = ((temp -min)/(max -min));
    }
    
}


/********************************************************
 This function  is to calculate distance between two points
 ********************************************************/

double cal_distance(double x1, double y1, double z1, double x2, double y2, double z2){
    return sqrt(pow((x1 - x2), 2)+pow((y1 - y2), 2)+pow((z1 - z2), 2));
}


/***********************************************************
 This is to create a team
 ***********************************************************/

void create_team(vector<population>* teams,int number_of_rovers,int number_of_routes,int generation){
    for (int team_number = 0; team_number<teams->size(); team_number++) {
        for (int rover =0; rover < teams->at(team_number).teamRover.size(); rover++) {
            vector<int> shuffle;
            for (int i = 0; i<number_of_routes; i++) {
                shuffle.push_back(i);
            }
            random_shuffle(shuffle.begin(), shuffle.end());
            assert(shuffle.size() == teams->at(team_number).teamRover.at(rover).new_network.size());
            for (int i=0; i< shuffle.size(); i++) {
                teams->at(team_number).teamRover.at(rover).new_network.at(shuffle.at(i)).team_number=i;
            }
        }
    }
}


/********************************************************
 This function initialize all the environment
 ********************************************************/
void initial_team(vector<population>* teams,vector<vector<double>>* location_obstacle,int number_of_obstacles, vector<vector<double>>* p_stat, double distance_between_rover){
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0; rover < teams->at(team_number).teamRover.size(); rover++) {
            //Setting target location here
            //Location of target 1
            teams->at(team_number).teamRover.at(rover).target_x = 4.0+(distance_between_rover*rover);
            teams->at(team_number).teamRover.at(rover).target_y = 20.0;
            teams->at(team_number).teamRover.at(rover).target_z = 0.0;
            //Location of target 2
//            teams->at(team_number).teamRover.at(rover).target_x_1 = 28.0+(distance_between_rover*rover);
//            teams->at(team_number).teamRover.at(rover).target_y_1 = 7.0;
        }
        
        //reseting the rover to initial location
        for (int rover = 0 ; rover <teams->at(team_number).teamRover.size(); rover++) {
            teams->at(team_number).teamRover.at(rover).x_location_new = p_stat->at(rover).at(0);
            teams->at(team_number).teamRover.at(rover).y_location_new = p_stat->at(rover).at(1);
            teams->at(team_number).teamRover.at(rover).z_location_new = p_stat->at(rover).at(2);
            // teams->at(team_number).teamRover.at(rover).velocity_left = 0.1;
            // teams->at(team_number).teamRover.at(rover).velocity_right = 0.1; 
            teams->at(team_number).teamRover.at(rover).length_of_rover = 1;
        }
        
        location_obstacle->clear();
        
        for (int ob = 0 ; ob < number_of_obstacles; ob++) {
            double rand_1 = random_global(750);
            double rand_2 = random_global(750);
            double rand_3 = random_global(750);
            
            vector<double> temp;
            temp.push_back(rand_1);
            temp.push_back(rand_2);
            temp.push_back(rand_3);
            
            //Check if rand_1 or rand_2 is on or near
            location_obstacle->push_back(temp);
            temp.clear();
        }
    }
}

/**************************************************************************************************
 * Calculates the time taken for each rover
 * ************************************************************************/

int cal_time_unicycle_movement(vector<population>* teams, int population_number, int rover, int  team_value, double current_temp_x, double current_temp_y, double move_to_x, double move_to_y){
    bool flag_loop_fun = true;
    vector<double> store_x_location;
    vector<double> store_y_location;
    while (flag_loop_fun)
    {
        double temp_difference_x = abs(move_to_x - current_temp_x);
        double temp_difference_y = abs(move_to_y - current_temp_y);
        // cout<<current_temp_x<<"\t"<<current_temp_y<<"\t"<<move_to_x<<"\t"<<move_to_y<<endl;
        
        if ((temp_difference_x  < 0.1)&& (temp_difference_y < 0.1))
        {
            flag_loop_fun = false;
        }
        
        double aim_x = move_to_x - current_temp_x;
        double aim_y = move_to_y - current_temp_y;
        double aim_theta = atan2(aim_y, aim_x);
        double dt = 1;

        double omega = aim_theta;
        double x_dot = 0.1*cos(aim_theta);
        double y_dot = 0.1*sin(aim_theta);

        current_temp_x += (x_dot * dt);
        current_temp_y += (y_dot * dt);     
        store_x_location.push_back(current_temp_x);
        store_y_location.push_back(current_temp_y);
    }

    return store_x_location.size();
}

/**************************************************************************************
 * Actual movement of the rovers with change in velocity
 * *********************************************************************************/
void unicycle_movement(vector<population>* teams, int population_number, int  team_value, int current_time_step, int max_time_steps){
    // cout<<teams->at(population_number).teamRover.size()<<endl;
    int previous_time_step = current_time_step -1 ;
    for (int rover = 0; rover < teams->at(population_number).teamRover.size(); rover++)
    {
        double temp_initial_x = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(previous_time_step);
        double temp_initial_y = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(previous_time_step);
        double temp_finial_x = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(current_time_step);
        double temp_finial_y = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(current_time_step);

        double distance_between = cal_distance(temp_initial_x, temp_initial_y, 0, temp_finial_x, temp_finial_y, 0);
        double velocity = distance_between/max_time_steps;
        // teams->at(population_number).teamRover.at(rover)
        for (int  working_time_step = 0; working_time_step < max_time_steps; working_time_step++)
        {
            double temp_difference_x = temp_finial_x - temp_initial_x;
            double temp_difference_y = temp_finial_y - temp_initial_y;
            double temp_angle = atan2(temp_difference_y, temp_difference_x);
        
            double omega = temp_angle;
            // cout<<temp_initial_x<<"\t"<<temp_initial_y<<endl;
            temp_initial_x += velocity*cos(temp_angle);
            temp_initial_y += velocity*sin(temp_angle);
            teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates_unicycle.push_back(temp_initial_x);
            teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates_unicycle.push_back(temp_initial_y);
        }
        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).velocity_left = 0;
    }
    
}



/*******************************************************
 This function runs through each simulation
 *******************************************************/

void simulation_team(vector<population>* teams, vector<vector<double>>* p_location_obstacle,int generation,int number_of_obstacles, vector<vector<double>>* p_stat, double distance_between_rover,int number_of_routes,int number_of_rovers){
    int max_time_step = 40;
    for (int population_number =0 ; population_number< teams->size(); population_number++) {
        for (int team_value = 0 ; team_value < number_of_routes ; team_value++) {
            initial_team(teams, p_location_obstacle,number_of_obstacles,p_stat, distance_between_rover);
            for (int time_step = 0 ; time_step < max_time_step; time_step++) {
                // cout<<"This is time step \t:"<<time_step<<endl;
                vector<int> store_time_steps;
                for (int rover = 0 ; rover < number_of_rovers; rover++) {
                    
                    //Save the x and y coordinates
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.push_back(teams->at(population_number).teamRover.at(rover).x_location_new);
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.push_back(teams->at(population_number).teamRover.at(rover).y_location_new);
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).z_coordinates.push_back(teams->at(population_number).teamRover.at(rover).z_location_new);
                    // cout<<"Rover location"<<teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(time_step)<<"\t"<<teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(time_step)<<"\t"<<teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).z_coordinates.at(time_step)<<endl;
                    //Reset sensor values
                    teams->at(population_number).teamRover.at(rover).reset_sensor_value();
                    
                    //sense all other rovers
                    for (int other_rover = 0 ; other_rover < teams->at(population_number).teamRover.size(); other_rover++) {
                        if (rover != other_rover) {
                            teams->at(population_number).teamRover.at(rover).sense_new_rover(teams->at(population_number).teamRover.at(other_rover).x_location_new, teams->at(population_number).teamRover.at(other_rover).y_location_new,teams->at(population_number).teamRover.at(other_rover).z_location_new);
                        }
                    }
                    
                    //sense target location
                    teams->at(population_number).teamRover.at(rover).sense_new_target(teams->at(population_number).teamRover.at(rover).target_x, teams->at(population_number).teamRover.at(rover).target_y, teams->at(population_number).teamRover.at(rover).target_z);
                    
                    
                    //sense obstacles
                    for (int obstacle = 0; obstacle< p_location_obstacle->size(); obstacle++) {
                        teams->at(population_number).teamRover.at(rover).sense_new_ob(p_location_obstacle->at(obstacle).at(0), p_location_obstacle->at(obstacle).at(1),p_location_obstacle->at(obstacle).at(2));
                    }
                    
                    //sense target location 2
//                    teams->at(population_number).teamRover.at(rover).sense_new_target_1(teams->at(population_number).teamRover.at(rover).target_x_1, teams->at(population_number).teamRover.at(rover).target_y_1);
                    
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).outputvaluesNN.clear();
                    
                    
                    //Pass sensor values to neural network and obtain new teleportation point
                    // cout<<teams->at(population_number).teamRover.at(rover).sensor.size()<<endl;
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).feedForward(teams->at(population_number).teamRover.at(rover).sensor);
                    
                    
                    //Out put from neural network
                    double dx = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).outputvaluesNN.at(0);
                    double dy = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).outputvaluesNN.at(1);
                    double dz = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).outputvaluesNN.at(2);
                    
                    //Here the movement of rover has to happen
                    double temp_current_x = teams->at(population_number).teamRover.at(rover).x_location_new;
                    double temp_current_y = teams->at(population_number).teamRover.at(rover).y_location_new;

                    //cout<< teams->at(population_number).teamRover.at(rover).x_location_new<<"\t"<<teams->at(population_number).teamRover.at(rover).y_location_new<<endl;
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).outputvaluesNN.clear();
                    teams->at(population_number).teamRover.at(rover).sensor.clear();
                    
                    //New location of rovers
                    teams->at(population_number).teamRover.at(rover).x_location_new += dx;
                    teams->at(population_number).teamRover.at(rover).y_location_new += dy;
                    teams->at(population_number).teamRover.at(rover).z_location_new += dz;
                    //cout<< teams->at(population_number).teamRover.at(rover).x_location_new<<"\t"<<teams->at(population_number).teamRover.at(rover).y_location_new<<endl;
                    double move_to_x = teams->at(population_number).teamRover.at(rover).x_location_new;
                    double move_to_y = teams->at(population_number).teamRover.at(rover).y_location_new;

                    store_time_steps.push_back(cal_time_unicycle_movement(teams, population_number, rover, team_value,  temp_current_x, temp_current_y, move_to_x, move_to_y));
                }
                if (time_step != 0)
                {
                    assert(store_time_steps.size() == number_of_rovers);
                    //This is for development
                    // for (int  rover = 0; rover < number_of_rovers; rover++)
                    // {
                    //     for (int  location = 0; location < teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.size(); location++)
                    //     {
                    //         cout<<"Rover location"<<teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(location)<<"\t"<<teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(location)<<"\t"<<teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).z_coordinates.at(location)<<endl;
                            
                    //     }
                    // }
                    
                    int time_for_unicycle = *min_element(store_time_steps.begin(), store_time_steps.end());
                    unicycle_movement(teams, population_number, team_value, time_step, time_for_unicycle);
                }
            }
            
        }
    }
    
    
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0 ; rover < teams->at(team_number).teamRover.size(); rover++) {
            for (int neural = 0 ; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates.size() == max_time_step);
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates.size() == teams->at(team_number).teamRover.at(rover).new_network.at(neural).y_coordinates.size() );
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates.size() == teams->at(team_number).teamRover.at(rover).new_network.at(neural).z_coordinates.size() );
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates_unicycle.size() == teams->at(team_number).teamRover.at(rover).new_network.at(neural).y_coordinates_unicycle.size() );
            }
        }
    }
}


/********************************************************
 This function is to check if both x_1 and x_2 are in same coordinates.
 ********************************************************/

bool check_quad(double x_1, double x_2){
    if ((x_1 >=0)&& (x_2>=0)) {
        return true;
    }else if ((x_1 < 0)&& (x_2 <0)){
        return  true;
    }
    
    return false;
    
}

/********************************************************
 This function is to calculate the following:
 1. Distance between each rover
 2. Distance to the target
 3. Distance to each obstacle
 ********************************************************/

void distance_team(vector<population>* teams, double distance_between_rover, double safe_distance_between_rover, double radius_of_obstacle, vector<vector<double>>* p_location_obstacle,int number_of_objectives){
    for (int population_number = 0 ; population_number < teams->size(); population_number++) {
        for (int team_value = 0 ; team_value < teams->at(population_number).path_numbers.size(); team_value++) {
            for (int rover = 0 ; rover < teams->at(population_number).path_numbers.at(team_value).size(); rover++) {
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).summation_hitting= 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_agents_summation= 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance= 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance_1= 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_target_1 = 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_target_2 = 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_agent = 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_obstacle = 0.0;
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.clear();
                
                
                //distance to target
                for (int index = 0; index < teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.size(); index++) {
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).target_distance.push_back(cal_distance(teams->at(population_number).teamRover.at(rover).target_x, teams->at(population_number).teamRover.at(rover).target_y,teams->at(population_number).teamRover.at(rover).target_z, teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(index), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(index),teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).z_coordinates.at(index))); 
                }
                
                
                //distance to target_1
//                for (int index = 0; index < teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.size(); index++) {
//                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).target_distance_1.push_back(cal_distance(teams->at(population_number).teamRover.at(rover).target_x_1, teams->at(population_number).teamRover.at(rover).target_y_1, teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(index), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(index)));
//                }
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance = *std::min_element(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).target_distance.begin(), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).target_distance.end());
                 //teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance_1 = *std::min_element(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).target_distance_1.begin(), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).target_distance_1.end());
                
                
                if (teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance > 0.50) {
                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance *= 1000;
                }
                
//                if (teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance_1 > 0.50) {
//                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance_1 *= 1000;
//                }
                
                //each obstacle distance
                for (int index = 0 ; index < p_location_obstacle->size(); index++) {
                    vector<double> temp_distance;
                    //Point generator
                    for (int x = 0; x < teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.size(); x++) {
                        double temp_cal_distance = cal_distance(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(x), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(x),teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).z_coordinates.at(x), p_location_obstacle->at(index).at(0), p_location_obstacle->at(index).at(1),p_location_obstacle->at(index).at(2));
                        temp_distance.push_back(temp_cal_distance);
                        
                        //Punishment
                        if (temp_cal_distance < radius_of_obstacle) {
                            teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_obstacle += 1000;
                        }
                    }
                    //unicycle
                    for (int x = 0; x < teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates_unicycle.size(); x++) {
                        double temp_cal_distance = cal_distance(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates_unicycle.at(x), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates_unicycle.at(x),0, p_location_obstacle->at(index).at(0), p_location_obstacle->at(index).at(1),p_location_obstacle->at(index).at(2));
                        temp_distance.push_back(temp_cal_distance);
                        
                        //Punishment
                        if (temp_cal_distance < radius_of_obstacle) {
                            teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_obstacle += 1000;
                        }
                    }

                    teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).obstacle_distance.push_back(temp_distance);
                    temp_distance.clear();
                }
                
                
                //Hitting other agents
                for (int other_rover = 0 ; other_rover < teams->at(population_number).path_numbers.at(team_value).size(); other_rover++) {
                    if (rover != other_rover) {
                        vector<double> temp_distance;
                        for (int index = 0 ; index < teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.size(); index++) {
                            double temp_distance_cal = cal_distance(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates.at(index), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates.at(index),teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).z_coordinates.at(index), teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).x_coordinates.at(index), teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).y_coordinates.at(index),teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).z_coordinates.at(index));
                            temp_distance.push_back(temp_distance_cal);
                            if (temp_distance_cal < safe_distance_between_rover){
                                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_agents_summation += 1000;
                            }else if (temp_distance_cal > (safe_distance_between_rover+1.0)){
                                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_agents_summation += 1000;
                            }
                        }
                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).other_rover_paths.push_back(temp_distance);

                        vector<double> temp_distance_new;
                        for (int index = 0 ; index < teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates_unicycle.size(); index++) {
                            double temp_distance_cal = cal_distance(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).x_coordinates_unicycle.at(index), teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).y_coordinates_unicycle.at(index), 0, teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).x_coordinates_unicycle.at(index), teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).y_coordinates_unicycle.at(index), 0);
                            temp_distance_new.push_back(temp_distance_cal);
                            if (temp_distance_cal < safe_distance_between_rover){
                                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_agents_summation += 1000;
                            }else if (temp_distance_cal > (safe_distance_between_rover+1.0)){
                                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_agents_summation += 1000;
                            }
                        }
                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).other_rover_paths.push_back(temp_distance_new);

                    }
                }
                
                
                
            }
            
           
            double total_punishment_formation =0.0;
            
            //Now formation for each team global
            for (int time_step = 0; time_step < teams->at(population_number).teamRover.at(0).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(0)).x_coordinates.size(); time_step++) {
                for (int other_rover = 0; other_rover < teams->at(population_number).path_numbers.at(team_value).size(); other_rover++) {
                    if( (other_rover != 0) &&(other_rover != teams->at(population_number).path_numbers.at(team_value).size() -1) ){
                        
                        vector<double> pa;
                        vector<double> ba;
                        double dot_pa_ba = 0.0,dot_ba_ba = 0.0;
                        pa.push_back(teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).x_coordinates.at(time_step) - teams->at(population_number).teamRover.at(0).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(0)).x_coordinates.at(time_step));
                        
                        pa.push_back(teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).y_coordinates.at(time_step) - teams->at(population_number).teamRover.at(0).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(0)).y_coordinates.at(time_step));
                        
                        pa.push_back(teams->at(population_number).teamRover.at(other_rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(other_rover)).z_coordinates.at(time_step) - teams->at(population_number).teamRover.at(0).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(0)).z_coordinates.at(time_step));
                        ba.push_back(teams->at(population_number).teamRover.at(teams->at(population_number).teamRover.size()-1).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(teams->at(population_number).path_numbers.at(team_value).size()-1)).x_coordinates.at(time_step) - teams->at(population_number).teamRover.at(0).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(0)).x_coordinates.at(time_step));
                        ba.push_back(teams->at(population_number).teamRover.at(teams->at(population_number).teamRover.size()-1).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(teams->at(population_number).path_numbers.at(team_value).size()-1)).y_coordinates.at(time_step) - teams->at(population_number).teamRover.at(0).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(0)).y_coordinates.at(time_step));
                        ba.push_back(teams->at(population_number).teamRover.at(teams->at(population_number).teamRover.size()-1).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(teams->at(population_number).path_numbers.at(team_value).size()-1)).z_coordinates.at(time_step) - teams->at(population_number).teamRover.at(0).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(0)).z_coordinates.at(time_step));
                        
                        
                        for (int objective = 0 ; objective < pa.size(); objective++) {
                            dot_pa_ba += (pa.at(objective)*ba.at(objective));
                            dot_ba_ba += (ba.at(objective)*ba.at(objective));
                        }
                        double t = (dot_pa_ba/dot_ba_ba);
                        double distance = 0.0;
                        for (int i =0; i<ba.size(); i++) {
                            distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                        }
                        distance = sqrt(distance);
                        //cout<<distance<<endl;
                        //cout<<total_punishment_formation<<endl;
                        if (distance> 0.15) {
                            total_punishment_formation += 1000;
                        }
                    }
                }
            }
            
            if (total_punishment_formation > 1000) {
                total_punishment_formation *= 100;
            }
            
            
            double temp_target_1 = 0.0;
            //double temp_target_2 = 0.0;
            double temp_hitting_agent_summation = 0.0;
            double temp_hittin_obstacle = 0.0;
            
            
            //This is doing summation of team values only
            for (int rover = 0 ; rover < teams->at(population_number).path_numbers.at(team_value).size(); rover++) {
                
                temp_target_1 +=teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance;
                
                
                //temp_target_2 += teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance_1;
                
                temp_hitting_agent_summation += teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_agents_summation;
                
                temp_hittin_obstacle +=teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_obstacle;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).formation_of_team = total_punishment_formation;
                
            }
            
            
            for (int rover = 0 ; rover < teams->at(population_number).path_numbers.at(team_value).size(); rover++) {
                
                
                //We have to add formation here they should be technically
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_target_1 = temp_target_1;
                
                //teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_target_2 = temp_target_2;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_agent = temp_hitting_agent_summation;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_obstacle = temp_hittin_obstacle;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_summation_hitting = temp_hitting_agent_summation + temp_hittin_obstacle;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_target_1 = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_target_1 - teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_target_2 = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_target_2 - teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).shortest_target_distance_1;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_agent = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_agent - teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_agents_summation;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_obstacle = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_obstacle - teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).hitting_obstacle;
                
                teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_summation_hitting = teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_agent + teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_obstacle;
                
                int fitness_case_number = 0;
                switch (fitness_case_number) {
                    case 0:
                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_target_1);
                        //teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_target_2);
                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).global_summation_hitting);
                         teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).formation_of_team);
                        break;
                    case 1:
                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_target_1);
//                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_target_2);
                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_summation_hitting);
//                        teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.push_back(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).difference_formation);
                        break;
                        
                    default:
                        break;
                }
                
                assert(teams->at(population_number).teamRover.at(rover).new_network.at(teams->at(population_number).path_numbers.at(team_value).at(rover)).fintess_values.size() == number_of_objectives);
                
            }
        }
    }
    
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0 ; rover < teams->at(team_number).teamRover.size(); rover++) {
            for (int neural = 0 ; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(neural).fintess_values.size() == number_of_objectives);
            }
        }
    }
    
    
}

void normalization(vector<population>* teams,int number_of_objectives){
    for (int population = 0 ; population < teams->size(); population++) {
        for (int rover = 0 ; rover < teams->at(population).teamRover.size(); rover++) {
            for (int ob_number = 0 ; ob_number < number_of_objectives; ob_number++) {
                vector<double> stored_values;
                for (int neural = 0 ; neural < teams->at(population).teamRover.at(rover).new_network.size(); neural++) {
                    stored_values.push_back(teams->at(population).teamRover.at(rover).new_network.at(neural).fintess_values.at(ob_number));
                }
                double max_fitness = *std::max_element(stored_values.begin(), stored_values.end());
                double min_fitness = *std::min_element(stored_values.begin(), stored_values.end());
                
                for (int neural = 0 ; neural < teams->at(population).teamRover.at(rover).new_network.size(); neural++) {
                    teams->at(population).teamRover.at(rover).new_network.at(neural).normalized_fitness_values.push_back((teams->at(population).teamRover.at(rover).new_network.at(neural).fintess_values.at(ob_number) - min_fitness)/(max_fitness-min_fitness));
                    
                    
                }
                
            }
        }
    }
    
    for (int population = 0; population < teams->size(); population++) {
        for (int rover = 0 ; rover < teams->at(population).teamRover.size(); rover++) {
            for (int neural = 0; neural < teams->at(population).teamRover.at(rover).new_network.size(); neural++) {
                assert(teams->at(population).teamRover.at(rover).new_network.at(neural).normalized_fitness_values.size() == number_of_objectives);
            }
        }
    }
}

void save_team_numbers(vector<population>* teams,int generation,int number_of_rovers, int number_of_routes){
    for (int population_number = 0 ; population_number < teams->size();population_number++) {
        teams->at(population_number).path_numbers.clear();
        for (int team_value = 0 ; team_value < number_of_routes; team_value++) {
            vector<int> temp_team;
            for (int rover = 0; rover < number_of_rovers; rover++) {
                for (int neural_network = 0 ; neural_network < number_of_routes; neural_network++) {
                    if (team_value == teams->at(population_number).teamRover.at(rover).new_network.at(neural_network).team_number) {
                        temp_team.push_back(neural_network);
                        break;
                    }
                }
            }
            teams->at(population_number).path_numbers.push_back(temp_team);
            assert(temp_team.size() == number_of_rovers);
        }
        assert(teams->at(population_number).path_numbers.size() == number_of_routes);
    }
    
}

void ea(vector<population>* teams){
    int number_of_rover = teams->at(0).teamRover.size();
    int number_of_routes = teams->at(0).teamRover.at(0).new_network.size();
    
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0; rover < teams->at(team_number).teamRover.size(); rover++) {
            for (int route = 0 ; route < (number_of_routes/2); route++) {
                int rand_1 = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
                int rand_2 = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
                while (rand_1 == rand_2) {
                    rand_1 = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
                    rand_2 = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
                }
                
                double rand_1_fitness = 0.0, rand_2_fitness = 0.0;
                
                for (int index = 0 ;index < teams->at(team_number).teamRover.at(rover).new_network.at(rand_1).fintess_values.size() ; index++) {
                    rand_1_fitness += teams->at(team_number).teamRover.at(rover).new_network.at(rand_1).fintess_values.at(index);
                    rand_2_fitness += teams->at(team_number).teamRover.at(rover).new_network.at(rand_2).fintess_values.at(index);
                }
                
                if ((rand_1_fitness) < (rand_2_fitness)){
                    //remove rand_2
                    teams->at(team_number).teamRover.at(rover).new_network.erase(teams->at(team_number).teamRover.at(rover).new_network.begin()+rand_2);
                }else{
                    //remove rand_1
                    teams->at(team_number).teamRover.at(rover).new_network.erase(teams->at(team_number).teamRover.at(rover).new_network.begin()+rand_1);
                }
            }
            assert(teams->at(team_number).teamRover.at(rover).new_network.size() == (number_of_routes/2));
            
            
            for (int route = (number_of_routes/2); route < number_of_routes; route++) {
                int rand_1 = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
                teams->at(team_number).teamRover.at(rover).new_network.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(rand_1));
                teams->at(team_number).teamRover.at(rover).new_network.at(teams->at(team_number).teamRover.at(rover).new_network.size()-1).mutate();
            }
            
            //            for (int route = 0 ; route < (number_of_routes/2); route++) {
            //                int rand_1 = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
            //                teams->at(team_number).teamRover.at(rover).new_network.at(rand_1).mutate();
            //            }
        }
    }
}

/************************************
 NSGA II
 *************************************/
bool compare_two_index(vector<population>* teams,int team_number, int rover ,int neural,int other_neural){
    
    for (int index = 0 ; index < teams->at(team_number).teamRover.at(rover).new_network.at(neural).fintess_values.size(); index++) {
        if (teams->at(team_number).teamRover.at(rover).new_network.at(neural).normalized_fitness_values.at(index) < teams->at(team_number).teamRover.at(rover).new_network.at(other_neural).normalized_fitness_values.at(index)) {
            return true;
        }
    }
    
    return false;
}

void nsga_ii(vector<population>* teams,int number_of_objectives,int generation){
    
    //First create fronts
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0; rover < teams->at(team_number).teamRover.size(); rover++) {
            int number_of_neurals = teams->at(team_number).teamRover.at(rover).new_network.size();
            // For each route we are sorting them
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).getting_dominated_by = 0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).front_number = -9999;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).in_front = false;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).remove_me = false;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).crowding_distance = 0;
                for (int other_neural = 0; other_neural < teams->at(team_number).teamRover.at(rover).new_network.size(); other_neural++) {
                    if (neural != other_neural) {
                        bool flag_value = compare_two_index(teams, team_number, rover, neural, other_neural);
                        if (flag_value) {
                            teams->at(team_number).teamRover.at(rover).new_network.at(neural).dominating_them.push_back(other_neural);// All the individuals index is dominating
                        }else{
                            teams->at(team_number).teamRover.at(rover).new_network.at(neural).getting_dominated_by++;//How many are dominating index
                        }
                    }
                }
                
            }
            
            //pushes all the dominating values
            vector<int> all_sizes;
            vector<vector<int>> fronts;
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(neural).in_front == false) {
                    all_sizes.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(neural).dominating_them.size());
                }
            }
            sort(all_sizes.begin(), all_sizes.end(), std::greater<>()); // sort from high to low
            all_sizes.erase( unique( all_sizes.begin(), all_sizes.end() ), all_sizes.end() );// remove all repeating once
            
            //all get ranked
            for (int rank = 0; rank < all_sizes.size(); rank++) {
                vector<int> temp_front;
                for (int index = 0; index < teams->at(team_number).teamRover.at(rover).new_network.size(); index++) {
                    if (teams->at(team_number).teamRover.at(rover).new_network.at(index).dominating_them.size() == all_sizes.at(rank)) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(index).front_number = rank;
                        teams->at(team_number).teamRover.at(rover).new_network.at(index).in_front = true;
                        temp_front.push_back(index);
                    }
                }
                fronts.push_back(temp_front);
                temp_front.clear();
            }
            
            for (int index = 0 ; index < teams->at(team_number).teamRover.at(rover).new_network.size(); index++) {
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(index).front_number != -9999);
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(index).in_front);
            }
            
            vector<int> asperfront; // values are stored as per fronts.
            for (int i = 0; i< fronts.size(); i++) {
                for (int j = 0; j< fronts.at(i).size(); j++) {
                    asperfront.push_back(fronts.at(i).at(j));
                }
            }
            
            int current_number = 0;
            int required_number = 0;
            int front_number_to_select = -999;   //This is front which you need to play
            required_number = teams->at(team_number).teamRover.at(rover).new_network.size()/2;//This is making 4
            //cout<<required_number<<endl;
            for (int front_number = 0 ; front_number < fronts.size(); front_number++) {
                current_number = fronts.at(front_number).size();
                required_number -= current_number;
                if (required_number < 0) {
                    front_number_to_select = front_number;
                    break;
                }else if (required_number == 0){
                    front_number_to_select = 999;
                    break;
                }
            }
            
            if (front_number_to_select != 999) {
                //Crowding distance for selection from front_number_to_select
                for (int objective = 0 ; objective < number_of_objectives; objective++) {
                    //push all the values
                    vector<double> fitness_values;
                    for (int neural = 0 ; neural < fronts.at(front_number_to_select).size(); neural++) {
                        fitness_values.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(objective));
                        //cout<<teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(objective)<<endl;
                    }
                    
                    if (equal(fitness_values.begin() + 1, fitness_values.end(), fitness_values.begin())) {
                        //All fitness values are  equal
                        for (int neural = 0 ; neural < fronts.at(front_number_to_select).size(); neural++) {
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).crowding_distance += 9999999;
                        }
                    }else if(fronts.at(front_number_to_select).size() == 2){
                        //Which ever fitness is high give it good crowding distance
                        if ((teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).normalized_fitness_values.at(objective) )<= (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).normalized_fitness_values.at(objective))) {
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).crowding_distance +=9999999;
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).crowding_distance +=0;
                        }else{
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).crowding_distance +=9999999;
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).crowding_distance +=0;
                        }
                    }else{
                        sort(fitness_values.begin(), fitness_values.end(), std::greater<>()); // sort from high to low
                        vector<int> index_per_fitness;
                        std::vector<int>::iterator it;
                        
                        for (int fit = 0; fit<fitness_values.size(); fit++) {
                            for (int neural = 0 ; neural < fronts.at(front_number_to_select).size(); neural++) {
                                //check if fitness value match
                                if (fitness_values.at(fit) == teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(objective)) {
                                    
                                    it = find (index_per_fitness.begin(), index_per_fitness.end(),fronts.at(front_number_to_select).at(neural));
                                    
                                    if (it == index_per_fitness.end()){
                                        //Check if index  is already in the index_per_fitness
                                        index_per_fitness.push_back(fronts.at(front_number_to_select).at(neural));
                                        break;
                                    }
                                }
                            }
                        }
                        
                        assert(index_per_fitness.size() == fronts.at(front_number_to_select).size());
                        assert(index_per_fitness.size() == fitness_values.size());
                        
                        double minimum_value = fitness_values.at(fitness_values.size()-1);
                        double maximum_value = fitness_values.at(0);
                        double difference_value = maximum_value - minimum_value;
                        for (int index = 0 ; index < index_per_fitness.size(); index++) {
                            if ((index == 0)|| (index == (index_per_fitness.size()-1))) {
                                teams->at(team_number).teamRover.at(rover).new_network.at(index_per_fitness.at(index)).crowding_distance += 9999999;
                            }else{
                                int right_index = index + 1;
                                int left_index = index - 1;
                                teams->at(team_number).teamRover.at(rover).new_network.at(index_per_fitness.at(index)).crowding_distance += (((teams->at(team_number).teamRover.at(rover).new_network.at(index_per_fitness.at(left_index)).normalized_fitness_values.at(objective)) - (teams->at(team_number).teamRover.at(rover).new_network.at(index_per_fitness.at(right_index)).normalized_fitness_values.at(objective))) /(difference_value));
                            }
                        }
                    }
                    
                }
                
                //setting remove_me to remove bad once
                //First remove before crowding distance fronts
                for (int remove_front = (front_number_to_select+1); remove_front < fronts.size(); remove_front++) {
                    for (int index = 0 ; index < fronts.at(remove_front).size(); index++) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(remove_front).at(index)).remove_me = true;
                    }
                }
                //Now binary in crowding distance
                //If only two elements
                if (fronts.at(front_number_to_select).size() == 2) {
                    if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).crowding_distance > teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).crowding_distance) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).remove_me = true;
                    }else{
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).remove_me = true;
                    }
                }else{
                    current_number = fronts.at(front_number_to_select).size();
                    int select_number = current_number + required_number;
                    //                    for (int i = 0; i < fronts.at(front_number_to_select).size(); i++) {
                    //                        cout<<fronts.at(front_number_to_select).at(i)<<"\t";
                    //                    }
                    //                    cout<<endl;
                    //                    cout<<select_number<<endl;
                    //                    cout<<current_number<<endl;
                    //                    cout<<required_number<<endl;
                    for (int index = 0 ; index < (-required_number); index++) {
                        //cout<<"index:::"<<index<<endl;
                        int rand_index_1 = rand()%fronts.at(front_number_to_select).size();
                        int rand_index_2 = rand()%fronts.at(front_number_to_select).size();
                        bool check_all_three = true;
                        while (check_all_three) {
                            if (rand_index_1 == rand_index_2) {
                                rand_index_1 = rand()%fronts.at(front_number_to_select).size();
                                rand_index_2 = rand()%fronts.at(front_number_to_select).size();
                            }else if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(rand_index_2)).remove_me){
                                rand_index_2 = rand()%fronts.at(front_number_to_select).size();
                            }else if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(rand_index_1)).remove_me){
                                rand_index_1 = rand()%fronts.at(front_number_to_select).size();
                            }else{
                                check_all_three = false;
                            }
                        }
                        //cout<<rand_index_1<<"\t"<<rand_index_2<<endl;
                        
                        if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(rand_index_1)).crowding_distance > teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(rand_index_2)).crowding_distance) {
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(rand_index_2)).remove_me = true;
                        }else{
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(rand_index_1)).remove_me = true;
                        }
                    }
                }
                
            }else{
                //No crowding distance
                for (int index = (asperfront.size()-1); index >= (asperfront.size()/2); index--) {
                    teams->at(team_number).teamRover.at(rover).new_network.at(asperfront.at(index)).remove_me = true;
                }
            }
            
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(neural).remove_me) {
                    teams->at(team_number).teamRover.at(rover).new_network.erase(teams->at(team_number).teamRover.at(rover).new_network.begin()+neural);
                    neural = -1;
                }
            }
            //cout<<teams->at(team_number).teamRover.at(rover).new_network.size()<<endl;
            assert(teams->at(team_number).teamRover.at(rover).new_network.size() == (number_of_neurals/2));
            
            for (int neural = teams->at(team_number).teamRover.at(rover).new_network.size()  ; neural < (number_of_neurals); neural++) {
                int rand_1 = (rand()%(number_of_neurals/4));
                teams->at(team_number).teamRover.at(rover).new_network.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(rand_1));
                teams->at(team_number).teamRover.at(rover).new_network.at(teams->at(team_number).teamRover.at(rover).new_network.size()-1).mutate();
            }
            
            
            assert(teams->at(team_number).teamRover.at(rover).new_network.size() == (number_of_neurals));
        }
    }
    
}

/********************************************
 * NSGA III
 * ****************************************/

double cal_distance_two_vectors(vector<double> first_vector, vector<double> second_vector){
    vector<double> difference;
    for (int index = 0 ; index < first_vector.size(); index++) {
        difference.push_back(first_vector.at(index) - second_vector.at(index));
    }
    
    for (int index = 0 ; index < difference.size(); index++) {
        difference.at(index) = pow(difference.at(index), 2);
    }
    
    double distance_sumation = 0.0;
    for (int index = 0 ; index < difference.size(); index++) {
        distance_sumation += difference.at(index);
    }
    
    return sqrt(distance_sumation);
    
}

void nsga_iii(vector<population>* teams,int number_of_objectives,int generation){
    //First create fronts
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0; rover < teams->at(team_number).teamRover.size(); rover++) {
            int number_of_neurals = teams->at(team_number).teamRover.at(rover).new_network.size();
            // For each route we are sorting them
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).getting_dominated_by = 0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).front_number = -9999;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).in_front = false;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).remove_me = false;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).crowding_distance = 0;
                for (int other_neural = 0; other_neural < teams->at(team_number).teamRover.at(rover).new_network.size(); other_neural++) {
                    if (neural != other_neural) {
                        bool flag_value = compare_two_index(teams, team_number, rover, neural, other_neural);
                        if (flag_value) {
                            teams->at(team_number).teamRover.at(rover).new_network.at(neural).dominating_them.push_back(other_neural);// All the individuals index is dominating
                        }else{
                            teams->at(team_number).teamRover.at(rover).new_network.at(neural).getting_dominated_by++;//How many are dominating index
                        }
                    }
                }
                
            }
            
            //pushes all the dominating values
            vector<int> all_sizes;
            vector<vector<int>> fronts;
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(neural).in_front == false) {
                    all_sizes.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(neural).dominating_them.size());
                }
            }
            sort(all_sizes.begin(), all_sizes.end(), std::greater<>()); // sort from high to low
            all_sizes.erase( unique( all_sizes.begin(), all_sizes.end() ), all_sizes.end() );// remove all repeating once
            
            //all get ranked
            for (int rank = 0; rank < all_sizes.size(); rank++) {
                vector<int> temp_front;
                for (int index = 0; index < teams->at(team_number).teamRover.at(rover).new_network.size(); index++) {
                    if (teams->at(team_number).teamRover.at(rover).new_network.at(index).dominating_them.size() == all_sizes.at(rank)) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(index).front_number = rank;
                        teams->at(team_number).teamRover.at(rover).new_network.at(index).in_front = true;
                        temp_front.push_back(index);
                    }
                }
                fronts.push_back(temp_front);
                temp_front.clear();
            }
            
            for (int index = 0 ; index < teams->at(team_number).teamRover.at(rover).new_network.size(); index++) {
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(index).front_number != -9999);
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(index).in_front);
            }
            
            vector<int> asperfront; // values are stored as per fronts.
            for (int i = 0; i< fronts.size(); i++) {
                for (int j = 0; j< fronts.at(i).size(); j++) {
                    asperfront.push_back(fronts.at(i).at(j));
                }
            }
            
            double current_number = 0;
            double required_number = 0;
            int front_number_to_select = -999;   //This is front which you need to play
            required_number = (teams->at(team_number).teamRover.at(rover).new_network.size()/2);
            for (int front_number = 0 ; front_number < fronts.size(); front_number++) {
                current_number = fronts.at(front_number).size();
                //cout<<current_number<<endl;
                //cout<<required_number<<endl;
                required_number -= current_number;
                if (required_number < 0) {
                    front_number_to_select = front_number;
                    break;
                }else if (required_number == 0){
                    front_number_to_select = 999;
                    break;
                }
            }
            //cout<<required_number<<endl;
            
            if (front_number_to_select != 999) {
                //First save fitness values to once vector.
                if(fronts.at(front_number_to_select).size() == 2){
                    teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).remove_me = true;
                     teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).remove_me = true;
                    for (int objective = 0; objective < number_of_objectives; objective++) {
                        if ((teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).fintess_values.at(objective) )<= (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).fintess_values.at(objective))) {
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(0)).remove_me =false;
                            objective = number_of_objectives;
                        }else{
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(1)).remove_me =false;
                            objective = number_of_objectives;
                        }
                    }
                }else{
                    //Calculate distance to each reference line
                    int zero=0,one=0,two=0,three=0;
                    vector<int> index_zero;vector<int> index_one;vector<int> index_two;vector<int> index_three;
                    for (int neural =0; neural < fronts.at(front_number_to_select).size(); neural++) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).remove_me = true;
                        
                        if (number_of_objectives == 3) {
                            vector<double> distance_reference;
                            
                            //For first reference
                            vector<double> pa;
                            vector<double> ba;
                            double dot_pa_ba = 0.0,dot_ba_ba = 0.0;
                            for (int i=0; i<three_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - three_0.at(i));
                                ba.push_back(three_1.at(i) - three_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            
                            double t = (dot_pa_ba/dot_ba_ba);
                            double distance = 0.0;
                            for (int i =0; i<three_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);
                            distance_reference.push_back(distance);
                            
                            //second refernce
                            pa.clear();
                            ba.clear();
                            dot_pa_ba = 0.0;dot_ba_ba = 0.0;
                            for (int i=0; i<three_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - three_0.at(i));
                                ba.push_back(three_2.at(i) - three_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            t = 0.0;
                            t = (dot_pa_ba/dot_ba_ba);
                            distance = 0.0;
                            
                            for (int i =0; i<three_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);distance_reference.push_back(distance);
                            
                            //thrid refernce
                            pa.clear();
                            ba.clear();
                            dot_pa_ba = 0.0;dot_ba_ba = 0.0;
                            for (int i=0; i<three_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - three_0.at(i));
                                ba.push_back(three_3.at(i) - three_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            t = 0.0;
                            t = (dot_pa_ba/dot_ba_ba);
                            distance = 0.0;
                            
                            for (int i =0; i<three_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);distance_reference.push_back(distance);
                            
                            //fourth refernce
                            pa.clear();
                            ba.clear();
                            dot_pa_ba = 0.0; dot_ba_ba = 0.0;
                            for (int i=0; i<three_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - three_0.at(i));
                                ba.push_back(three_4.at(i) - three_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            t = 0.0;
                            t = (dot_pa_ba/dot_ba_ba);
                            distance = 0.0;
                            
                            for (int i =0; i<three_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);distance_reference.push_back(distance);
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).reference_line = min_element(distance_reference.begin(),distance_reference.end()) - distance_reference.begin();

                            
                        }else if (number_of_objectives == 4){
                            vector<double> distance_reference;
                            
                            //For first reference
                            vector<double> pa;
                            vector<double> ba;
                            double dot_pa_ba = 0.0,dot_ba_ba = 0.0;
                            for (int i=0; i<four_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - four_0.at(i));
                                ba.push_back(four_1.at(i) - four_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            
                            double t = (dot_pa_ba/dot_ba_ba);
                            double distance = 0.0;
                            for (int i =0; i<four_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);distance_reference.push_back(distance);
                            
                            //second refernce
                            pa.clear();
                            ba.clear();
                            dot_pa_ba = 0.0;dot_ba_ba = 0.0;
                            for (int i=0; i<four_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - four_0.at(i));
                                ba.push_back(four_2.at(i) - four_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            t = 0.0;
                            t = (dot_pa_ba/dot_ba_ba);
                            distance = 0.0;
                            
                            for (int i =0; i<four_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);distance_reference.push_back(distance);
                            
                            //thrid refernce
                            pa.clear();
                            ba.clear();
                            dot_pa_ba = 0.0;dot_ba_ba = 0.0;
                            for (int i=0; i<four_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - four_0.at(i));
                                ba.push_back(four_3.at(i) - four_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            t = 0.0;
                            t = (dot_pa_ba/dot_ba_ba);
                            distance = 0.0;
                            
                            for (int i =0; i<four_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);distance_reference.push_back(distance);
                            
                            //fourth refernce
                            pa.clear();
                            ba.clear();
                            dot_pa_ba = 0.0; dot_ba_ba = 0.0;
                            for (int i=0; i<four_0.size(); i++) {
                                pa.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).normalized_fitness_values.at(i) - four_0.at(i));
                                ba.push_back(four_4.at(i) - four_0.at(i));
                                dot_pa_ba += (pa.at(i)*ba.at(i));
                                dot_ba_ba += (ba.at(i)*ba.at(i));
                            }
                            t = 0.0;
                            t = (dot_pa_ba/dot_ba_ba);
                            distance = 0.0;
                            
                            for (int i =0; i<four_0.size(); i++) {
                                distance += (((t*ba.at(i))-pa.at(i))*((t*ba.at(i))-pa.at(i)));
                            }
                            distance = sqrt(distance);distance_reference.push_back(distance);
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).reference_line = min_element(distance_reference.begin(),distance_reference.end()) - distance_reference.begin();
                        }
                        
                        switch (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(neural)).reference_line) {
                            case 0:
                                zero++;
                                index_zero.push_back(fronts.at(front_number_to_select).at(neural));
                                break;
                        case 1:
                                one++;
                                index_one.push_back(fronts.at(front_number_to_select).at(neural));
                            break;
                        case 2:
                                two++;
                                index_two.push_back(fronts.at(front_number_to_select).at(neural));
                            break;
                        case 3:
                                three++;
                                index_three.push_back(fronts.at(front_number_to_select).at(neural));
                            break;
                            
                        }
                    }
                    
                    assert(zero == index_zero.size());
                    assert(one == index_one.size());
                    assert(two == index_two.size());
                    assert(three == index_three.size());
                    
                    current_number = fronts.at(front_number_to_select).size();
                    int select_number = current_number + required_number;
//                    cout<<"current_number \t "<<current_number<<endl;
//                    cout<<"required_number \t "<<required_number<<endl;
//                    cout<<"select_number \t "<<select_number<<endl;
                    //select which reference line to binary select
                    for (int needed = 0; needed < select_number; needed++) {
                        //cout<<"needed \t "<<needed<<endl;
                        int lowest = 999;
                        if ((zero != 0) && (lowest > zero)) {
                            lowest = zero;
                        }
                        if ((one != 0) && (lowest > one)) {
                            lowest = one;
                        }
                        if ((two != 0) && (lowest > two)) {
                            lowest = two;
                        }
                        if ((three != 0) && (lowest > three)) {
                            lowest = three;
                        }
                        
                        if (lowest == zero) {
                            //cout<<"In zero"<<endl;
                            int rand_nume = index_zero.size()-1;
                            teams->at(team_number).teamRover.at(rover).new_network.at(index_zero.at(rand_nume)).remove_me = false;
                            zero--;
                            index_zero.erase(index_zero.begin()+rand_nume);
                            
                        }else if (lowest == one) {
                            //cout<<"In one"<<endl;
                            int rand_nume = index_one.size()-1;
                            teams->at(team_number).teamRover.at(rover).new_network.at(index_one.at(rand_nume)).remove_me = false;
                            one--;
                            index_one.erase(index_one.begin()+rand_nume);
                        }else if (lowest == two) {
                            //cout<<"In two"<<endl;
                            int rand_nume = index_two.size()-1;
                            teams->at(team_number).teamRover.at(rover).new_network.at(index_two.at(rand_nume)).remove_me = false;
                            two--;
                            index_two.erase(index_two.begin()+rand_nume);
                        }else if (lowest == three) {
                            //cout<<"In three"<<endl;
                            int rand_nume = index_three.size()-1;
                            teams->at(team_number).teamRover.at(rover).new_network.at(index_three.at(rand_nume)).remove_me = false;
                            three--;
                            index_three.erase(index_three.begin()+rand_nume);
                        }
                        
                    }
                    
                    assert(zero == index_zero.size());
                    assert(one == index_one.size());
                    assert(two == index_two.size());
                    assert(three == index_three.size());
                    
                }
            
                //setting remove_me to remove bad once
                //First remove before crowding distance fronts
                for (int remove_front = (front_number_to_select+1); remove_front < fronts.size(); remove_front++) {
                    for (int index = 0 ; index < fronts.at(remove_front).size(); index++) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(remove_front).at(index)).remove_me = true;
                    }
                }
                
            }else{
                for (int index = (asperfront.size()-1); index >= (asperfront.size()/2); index--) {
                    teams->at(team_number).teamRover.at(rover).new_network.at(asperfront.at(index)).remove_me = true;
                }
            }
            
            
//            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
//                cout<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).remove_me<<"\t";
//            }
//            cout<<endl;
            
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(neural).remove_me) {
                    teams->at(team_number).teamRover.at(rover).new_network.erase(teams->at(team_number).teamRover.at(rover).new_network.begin()+neural);
                    neural = -1;
                }
            }
            
            assert(teams->at(team_number).teamRover.at(rover).new_network.size() == (number_of_neurals/2));
            
            for (int neural = teams->at(team_number).teamRover.at(rover).new_network.size()  ; neural < (number_of_neurals); neural++) {
                int rand_1 = (rand()%(number_of_neurals/2));
                teams->at(team_number).teamRover.at(rover).new_network.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(rand_1));
                teams->at(team_number).teamRover.at(rover).new_network.at(teams->at(team_number).teamRover.at(rover).new_network.size()-1).mutate();
            }
            //            for (int route = 0 ; route < (number_of_neurals/2); route++) {
            //                int rand_1 = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
            //                teams->at(team_number).teamRover.at(rover).new_network.at(rand_1).mutate();
            //            }
            
            assert(teams->at(team_number).teamRover.at(rover).new_network.size() == (number_of_neurals));
        }
    }

}

/*************************************************
 * M-PF 
 * ***********************************************/

void hof(vector<population>* teams,int number_of_objectives , int generation_number){
    
    
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0; rover < teams->at(team_number).teamRover.size(); rover++) {
            int number_of_neurals = teams->at(team_number).teamRover.at(rover).new_network.size();
            
            for (int individual = 0 ; individual < teams->at(team_number).teamRover.at(rover).new_network.size(); individual++) {
                teams->at(team_number).teamRover.at(rover).new_network.at(individual).getting_dominated_by = 0;
                teams->at(team_number).teamRover.at(rover).new_network.at(individual).front_number = -9999;
                teams->at(team_number).teamRover.at(rover).new_network.at(individual).in_front = false;
                teams->at(team_number).teamRover.at(rover).new_network.at(individual).remove_me = false;
                teams->at(team_number).teamRover.at(rover).new_network.at(individual).good_for_next_generation = false;
                teams->at(team_number).teamRover.at(rover).new_network.at(individual).crowding_distance = 0;
                for (int other_individual = 0; other_individual < teams->at(team_number).teamRover.at(rover).new_network.size(); other_individual++) {
                    if (individual != other_individual) {
                        bool flag_value = compare_two_index(teams, team_number, rover, individual, other_individual);
                        if (flag_value) {
                            teams->at(team_number).teamRover.at(rover).new_network.at(individual).dominating_them.push_back(other_individual);
                            //p_ind_population->at(indivdual).dominating_them.push_back(other_individual);// All the individuals index is dominating
                        }else{
                            teams->at(team_number).teamRover.at(rover).new_network.at(individual).getting_dominated_by++;
                            //p_ind_population->at(indivdual).getting_dominated_by++;//How many are dominating index
                        }
                    }
                }
            }
            
            //pushes all the dominating values
            vector<int> all_sizes;
            vector<vector<int>> fronts;
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(neural).in_front == false) {
                    all_sizes.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(neural).dominating_them.size());
                }
            }
            sort(all_sizes.begin(), all_sizes.end(), std::greater<>()); // sort from high to low
            all_sizes.erase( unique( all_sizes.begin(), all_sizes.end() ), all_sizes.end() );// remove all repeating once
            
            //all get ranked
            for (int rank = 0; rank < all_sizes.size(); rank++) {
                vector<int> temp_front;
                for (int index = 0; index < teams->at(team_number).teamRover.at(rover).new_network.size(); index++) {
                    if (teams->at(team_number).teamRover.at(rover).new_network.at(index).dominating_them.size() == all_sizes.at(rank)) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(index).front_number = rank;
                        teams->at(team_number).teamRover.at(rover).new_network.at(index).in_front = true;
                        temp_front.push_back(index);
                    }
                }
                fronts.push_back(temp_front);
                temp_front.clear();
            }
            
            for (int index = 0 ; index < teams->at(team_number).teamRover.at(rover).new_network.size(); index++) {
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(index).front_number != -9999);
                assert(teams->at(team_number).teamRover.at(rover).new_network.at(index).in_front);
            }

            vector<int> asperfront; // values are stored as per fronts.
            for (int i = 0; i< fronts.size(); i++) {
                for (int j = 0; j< fronts.at(i).size(); j++) {
                    asperfront.push_back(fronts.at(i).at(j));
                }
            }
            
            double entropy_h = 0.0;
            if (fronts.at(0).size() == 1) {
                entropy_h = 1.0;
            }else{
                entropy_h = 1/log(fronts.at(0).size());
            }
            
            
            vector<double> entropy_objectives;
            for (int objective = 0 ; objective < number_of_objectives; objective++) {
                //First summation of each objective
                double summation_of_fitness = 0.0;
                for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                    if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).fintess_values.at(objective) == 0) {
                        summation_of_fitness += 1;
                    }else{
                    
                    summation_of_fitness +=  teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).fintess_values.at(objective);
                    }
                }
                
                if (summation_of_fitness == 0) {
                    cout<<"Dig here"<<endl;
                }
                
                //Normalization of the fitness values
                for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                    if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).fintess_values.at(objective) == 0) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_values_hof.push_back(1/summation_of_fitness);
                    }else{
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_values_hof.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).fintess_values.at(objective)/summation_of_fitness);
                    }
                    
                }
                
            }
            

            for (int main_loop_objective = 0 ; main_loop_objective < number_of_objectives; main_loop_objective++) {
                double summation = 0.0;
                for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                    double temp_natural_log = 0.0;
                    if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_values_hof.at(main_loop_objective) == 0) {
                        temp_natural_log = 0.0;
                    }else if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_values_hof.at(main_loop_objective) <0){
                        temp_natural_log = log(-teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_values_hof.at(main_loop_objective));
                    }else{
                        temp_natural_log = log(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_values_hof.at(main_loop_objective));
                    }
                    
                    summation += (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_values_hof.at(main_loop_objective)*temp_natural_log);
                }
                entropy_objectives.push_back(summation*(-entropy_h));
            }
            assert(entropy_objectives.size() == number_of_objectives);
            
            vector<double> degree_of_diversification;
            double summation_of_diversification = 0.0;
            for (int objective = 0 ; objective < entropy_objectives.size(); objective++) {
                double temp = entropy_objectives.at(objective) -1;
                degree_of_diversification.push_back( temp);
                summation_of_diversification += temp;
            }
            assert(degree_of_diversification.size() == number_of_objectives);
            
            for (int objective = 0 ; objective < number_of_objectives; objective++) {
                degree_of_diversification.at(objective) /= summation_of_diversification;
            }
            
            //Now select best performing policy
            
            int best_index = 999999;
              double best_value = 99999999.99999;
              
              if (fronts.at(0).size() >= 2) {
                  //double weights = 0.50;
                  //cout<<weights<<endl;
                  vector<double> ideal_best;
                  vector<double> ideal_worst;
                  vector<int> index_ideal_best;
                  vector<int> index_ideal_worst;
                  
                  for (int objective = 0; objective < number_of_objectives; objective++) {
                      double summation_objective = 0.0;
                      for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                          summation_objective += (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).fintess_values.at(objective)); //*p_ind_population->at(fronts.at(0).at(individual)).fitnes_value.at(objective));
                          teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).euclidean_best = 9999999.99999;
                          teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).eculidean_worst = -9999999.99999;
                      }
                      //cout<<summation_objective<<endl;
                      
                      for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                          if (summation_objective == 0) {
                              summation_objective = 0.00001;
                          }
                          //cout<<summation_objective<<endl;
                          if (summation_objective < 0) {
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.push_back( degree_of_diversification.at(objective) * (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).fintess_values.at(objective)/sqrt(-summation_objective)));
                          }else{
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.push_back( degree_of_diversification.at(objective) * (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).fintess_values.at(objective)/sqrt(summation_objective)));
                          }
                      }
                      
                      double temp_ideal_best =999999999.99999;
                      double temp_ideal_worst =  -9999999999.99999;
                      int temp_index_ideal_best = 999999;
                      int temp_index_ideal_worst = 999999;
                      
                      for (int individual = 0; individual < fronts.at(0).size(); individual++) {
                          if (temp_ideal_best > teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(objective)) {
                              temp_ideal_best = teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(objective);
                              temp_index_ideal_best = individual;
                          }
                          
                          if (temp_ideal_worst < teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(objective)) {
                              temp_ideal_worst = teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(objective);
                              temp_index_ideal_worst = individual;
                          }
                      }
                      
                      if (temp_ideal_best == temp_ideal_worst) {
                          temp_index_ideal_best = rand()%fronts.at(0).size();
                          temp_index_ideal_worst = rand()%fronts.at(0).size();
                      }
                      
                      ideal_best.push_back(temp_ideal_best);
                      ideal_worst.push_back(temp_ideal_worst);
                      index_ideal_best.push_back(temp_index_ideal_best);
                      index_ideal_worst.push_back(temp_index_ideal_worst);
                  }
                  
                  if (fronts.at(0).size() != 2) {
                      for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                          double temp_best_summation = 0.0;
                          double temp_worst_summation = 0.0;
                          for (int objective = 0 ; objective < number_of_objectives ; objective++) {
                              temp_best_summation += pow(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(objective)-ideal_best.at(objective), 2);
                              temp_worst_summation += pow(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(objective)-ideal_worst.at(objective), 2);
                          }
                          if (temp_best_summation == 0) {
                              temp_best_summation = 0.00001;
                          }
                          if (temp_worst_summation == 0) {
                              temp_worst_summation = 0.00001;
                          }
                          
                          if (temp_best_summation < 0) {
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).euclidean_best = sqrt(-temp_best_summation);
                          }else{
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).euclidean_best = sqrt(temp_best_summation);
                          }
                          
                          if (temp_worst_summation < 0) {
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).eculidean_worst = sqrt(-temp_worst_summation);
                          }else{
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).eculidean_worst = sqrt(temp_worst_summation);
                          }
                          //p_ind_population->at(fronts.at(0).at(individual)).euclidean_best = sqrt(temp_best_summation);
                          //p_ind_population->at(fronts.at(0).at(individual)).eculidean_worst = sqrt(temp_worst_summation);
                          teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).performance_score = teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).eculidean_worst/(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).eculidean_worst+teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).euclidean_best);
                      }
                      
                      for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                          if (best_value >teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).performance_score) {
                              best_value = teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).performance_score;
                              best_index = individual;
                          }
                      }
                      if (best_index == 999999) {
                          cout<<"Work here"<<endl;
                      }
                      
                  }else{
                      for (int individual = 0; individual < fronts.at(0).size(); individual++) {
                          teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).summation_fitness_value = 0.0;
                          for (int fit = 0; fit < teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.size(); fit++) {
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(fit) = (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(fit) * degree_of_diversification.at(fit));
                              teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).summation_fitness_value += teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).normalized_fitness_topsis.at(fit);
                          }
                      }
                      if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(0)).summation_fitness_value < teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(1)).summation_fitness_value) {
                          best_index = 0;
                      }else{
                          best_index = 1;
                      }
                  }
              }else{
                  best_index = fronts.at(0).at(0);
              }
            
            for (int temp_individual = 0 ; temp_individual < fronts.at(0).size(); temp_individual++) {
                double summation = 0.0;
                for (int objective = 0 ; objective < number_of_objectives; objective++) {
                    summation += (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(temp_individual)).normalized_fitness_values_hof.at(objective) * degree_of_diversification.at(objective));
                }
                teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(temp_individual)).summation_fitness_value = summation;
                //cout<<p_ind_population->at(fronts.at(0).at(individual)).summation_fitness_value<<endl;
            }
            
            double lowest_value = 999999999.999999;
            for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).summation_fitness_value < lowest_value) {
                    lowest_value = teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).summation_fitness_value;
                    //p_ind_population->at(fronts.at(0).at(individual)).rank = 1;
                }
            }
            

            for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).summation_fitness_value == lowest_value) {
                    teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).rank = 1;
                }else{
                    teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).rank = 99999;
                }
            }
            
            int index_of_hall_fame_number = 99999;
            for (int individual = 0 ; individual < fronts.at(0).size(); individual++) {
                if(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).rank == 1){
                    teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).hall_of_fame = true;
                    teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).good_for_next_generation = true;
                    index_of_hall_fame_number = fronts.at(0).at(individual);
                }else{
                    teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(0).at(individual)).hall_of_fame = false;
                }
            }
            
            //Checking for number of individuals to select
            int current_number = 0;
            int required_number = 0;
            int front_number_to_select = -999;   //This is front which you need to play
            required_number = teams->at(team_number).teamRover.at(rover).new_network.size()/2;//This is making 4
            //cout<<required_number<<endl;
            for (int front_number = 0 ; front_number < fronts.size(); front_number++) {
                current_number = fronts.at(front_number).size();
                required_number -= current_number;
                if (required_number < 0) {
                    front_number_to_select = front_number;
                    break;
                }else if (required_number == 0){
                    front_number_to_select = 999;
                    break;
                }
            }
            
            //We have to apply HOF front_number_to_select
            if (front_number_to_select != 999) {
                //cout<<"This is the front number \t"<<front_number_to_select<<endl;
                //cout<<"This is the required number \t"<<required_number<<endl;
                
                //Fronts to remove
                for (int front_number_to_remove = front_number_to_select+1; front_number_to_remove <fronts.size(); front_number_to_remove++) {
                    for (int individual = 0; individual < fronts.at(front_number_to_remove).size(); individual++) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_remove).at(individual)).remove_me = true;
                    }
                }
                
                //Calculate the distance to HOF point to individual
                vector<double> values_fitness_hof ;
                vector<double> values_fitness_individual;
                
                
                for (int individual = 0 ; individual < fronts.at(front_number_to_select).size(); individual++) {
                   
                    for (int objective = 0; objective< number_of_objectives; objective++) {
                        values_fitness_individual.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(individual)).fintess_values.at(objective));
                        values_fitness_hof.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(index_of_hall_fame_number).fintess_values.at(objective));
                        
                    } teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(individual)).distance_to_hall_of_fame = cal_distance_two_vectors(values_fitness_individual, values_fitness_hof);
                    
                }
                
                //Sort them from low to high
               // cout<<required_number<<endl;
                //cout<<fronts.at(front_number_to_select).size()+required_number<<endl;
                
                int temp_required_values = fronts.at(front_number_to_select).size()+required_number;
                
                //cout<<"This is for the break"<<endl;
                
                
                vector<double> temp_distance;
                for (int temp = 0 ; temp < fronts.at(front_number_to_select).size(); temp++) {
                    temp_distance.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(temp)).distance_to_hall_of_fame);
                }
                
                sort(temp_distance.begin(), temp_distance.end());
                
                temp_distance.erase(temp_distance.begin()+temp_required_values,temp_distance.end());
                
                for (int temp_fit = 0 ; temp_fit < temp_distance.size(); temp_fit++) {
                    for (int individual = 0; individual< fronts.at(front_number_to_select).size() ; individual++) {
                        if ((temp_distance.at(temp_fit) == teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(individual)).distance_to_hall_of_fame) && (!teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(individual)).good_for_next_generation)){
                            teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(individual)).good_for_next_generation = true;
                            break;
                        }
                    }
                }
                
                for (int individual = 0 ; individual < fronts.at(front_number_to_select).size(); individual++) {
                    if (!teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(individual)).good_for_next_generation) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(fronts.at(front_number_to_select).at(individual)).remove_me = true;
                    }
                }
                
                
                
                
            }else{
                    //No crowding distance
                    for (int index = (asperfront.size()-1); index >= (asperfront.size()/2); index--) {
                        teams->at(team_number).teamRover.at(rover).new_network.at(asperfront.at(index)).remove_me = true;
                    }
                }
            
            
            //cout<<
            for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                if (teams->at(team_number).teamRover.at(rover).new_network.at(neural).remove_me) {
                    teams->at(team_number).teamRover.at(rover).new_network.erase(teams->at(team_number).teamRover.at(rover).new_network.begin()+neural);
                    neural = -1;
                }
            }
            //cout<<teams->at(team_number).teamRover.at(rover).new_network.size()<<endl;
            //cout<<p_ind_population->size()<<endl;
            
            while (teams->at(team_number).teamRover.at(rover).new_network.size() != (number_of_neurals/2)) {
                //int current_number_of_agents = teams->at(team_number).teamRover.at(rover).new_network.size();
                int rand_number_of_agent = rand()%teams->at(team_number).teamRover.at(rover).new_network.size();
                if (!teams->at(team_number).teamRover.at(rover).new_network.at(rand_number_of_agent).hall_of_fame) {
                    teams->at(team_number).teamRover.at(rover).new_network.erase(teams->at(team_number).teamRover.at(rover).new_network.begin()+rand_number_of_agent);
                }
            }
            
            
            if (teams->at(team_number).teamRover.at(rover).new_network.size() != (number_of_neurals/2)) {
                try {
                    ofstream testing;
                    char buf_testing[0x100];
                    snprintf(buf_testing, sizeof(buf_testing), "Broke.txt");
                    testing.open(buf_testing);
                    testing.exceptions(std::ifstream::failbit);
                    for (int individual = 0 ; individual < teams->at(team_number).teamRover.at(rover).new_network.size(); individual++) {
                        testing<<teams->at(team_number).teamRover.at(rover).new_network.at(individual).summation_fitness_value<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(individual).fintess_values.at(0)<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(individual).fintess_values.at(1)<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(individual). normalized_fitness_values_hof.at(0)<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(individual).normalized_fitness_values_hof.at(1) <<"\n";
                    }
                    testing<<"\n";
                    testing.close();
                } catch (std::ios_base::failure& fail) {
                    ofstream error_file;
                    error_file.open("error.txt");
                    error_file<<fail.what()<<"\n";
                    error_file.close();
                    cout<<fail.what()<<endl;
                    exit(1);
                }
                cout<<"something is wrong here"<<endl;
            }
            
            assert(teams->at(team_number).teamRover.at(rover).new_network.size() == (number_of_neurals/2));

            for (int neural = teams->at(team_number).teamRover.at(rover).new_network.size()  ; neural < (number_of_neurals); neural++) {
                int rand_1 = (rand()%(number_of_neurals/4));
                teams->at(team_number).teamRover.at(rover).new_network.push_back(teams->at(team_number).teamRover.at(rover).new_network.at(rand_1));
                teams->at(team_number).teamRover.at(rover).new_network.at(teams->at(team_number).teamRover.at(rover).new_network.size()-1).mutate();
                //mutate(p_ind_population,p_ind_population->size()-1,negative_value_accepted);
            }


            assert(teams->at(team_number).teamRover.at(rover).new_network.size() == (number_of_neurals));
        }
    }
    

}

void clear_teams(vector<population>* teams){
    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0 ; rover < teams->at(team_number).teamRover.size(); rover++) {
            for (int neural = 0 ; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).right_rover.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).left_rover.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).other_rover_paths.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).target_distance.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).target_distance_1.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).obstacle_distance.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).y_coordinates.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).z_coordinates.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).hitting_left_rover.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).hitting_right_rover.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).fintess_values.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).normalized_fitness_values.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).normalized_fitness_values_hof.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).normalized_fitness_topsis.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).hitting_agents_summation = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).summation_hitting = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).team_number = -999999;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).hitting_obstacle =0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).shortest_target_distance_1 = 9999999;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).shortest_target_distance = 999999;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).global_target_1 = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).global_target_2 = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).global_agent = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).global_obstacle = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).difference_target_1 = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).difference_target_2 = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).difference_agent = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).difference_obstacle = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).difference_formation = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).formation_of_team = 0.0;
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).swap_function();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates_unicycle.clear();
                teams->at(team_number).teamRover.at(rover).new_network.at(neural).y_coordinates_unicycle.clear();
            }
        }
    }
}

void print_values_to_file(int generation, vector<population>* teams , int number_of_generations){

    if ((generation == 0 )||(generation == (number_of_generations-1)))
    {
      for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0 ; rover < teams->at(team_number).teamRover.size(); rover++) {
            try {
                ofstream location_file;
                char buf_1[0x100];
                snprintf(buf_1, sizeof(buf_1), "/home/ak/Documents/gccProjects/HOF_flocking_simulation/Data/Development/Location_%d_%d_%d.txt", generation,team_number,rover);
                location_file.open(buf_1);
                for (int neural = 0 ; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                    for (int index = 0; index < teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates.size(); index++) {
                        location_file<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).team_number<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates.at(index)<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).y_coordinates.at(index)<<"\n";
                    }
                    location_file<<"\n";
                }
                location_file.close();
            } catch (exception &e) {
                ofstream error_file;
                error_file.open("error.txt");
                error_file<<e.what()<<"\n";
                error_file.close();
                exit(1);
            }
            
        }
    }

    for (int team_number = 0 ; team_number < teams->size(); team_number++) {
        for (int rover = 0 ; rover < teams->at(team_number).teamRover.size(); rover++) {
            try {
                ofstream location_file;
                char buf_1[0x100];
                snprintf(buf_1, sizeof(buf_1), "/home/ak/Documents/gccProjects/HOF_flocking_simulation/Data/Development/Unicycle_Location_%d_%d_%d.txt", generation,team_number,rover);
                location_file.open(buf_1);
                for (int neural = 0 ; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                    for (int index = 0; index < teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates_unicycle.size(); index++) {
                        location_file<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).team_number<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).x_coordinates_unicycle.at(index)<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).y_coordinates_unicycle.at(index)<<"\n";
                    }
                    location_file<<"\n";
                }
                location_file.close();
            } catch (exception &e) {
                ofstream error_file;
                error_file.open("error.txt");
                error_file<<e.what()<<"\n";
                error_file.close();
                exit(1);
            }
            
        }
    }
    
    //print rewards
    try {
        ofstream reward_file;
        char buf_2[0x100];
        snprintf(buf_2, sizeof(buf_2), "/home/ak/Documents/gccProjects/HOF_flocking_simulation/Data/Development/rewards_%d.txt", generation);
        reward_file.open(buf_2);
        reward_file.exceptions(std::ifstream::failbit);
        for (int team_number = 0 ; team_number < teams->size(); team_number++) {
            for (int rover = 0 ; rover < 1; rover++) {
                for (int neural = 0; neural < teams->at(team_number).teamRover.at(rover).new_network.size(); neural++) {
                    reward_file<< team_number<<"\t"<<rover<<"\t"<<neural<<"\t"<<teams->at(team_number).teamRover.at(rover).new_network.at(neural).team_number<<"\t";
                    for (int index = 0; index < teams->at(team_number).teamRover.at(rover).new_network.at(neural).fintess_values.size(); index++) {
                        reward_file<< teams->at(team_number).teamRover.at(rover).new_network.at(neural).fintess_values.at(index)<<"\t";
                    }
                    reward_file<< "\n";
                }
            }
        }
        reward_file.close();
    } catch (std::ios_base::failure& fail) {
        ofstream error_file;
        error_file.open("error.txt");
        error_file<<fail.what()<<"\n";
        error_file.close();
        cout<<fail.what()<<endl;
        exit(1);
    }  
    }
    

}

void run_simulation_function(){
    
    int pop_size = 1;
    int number_of_rover = 3;
    int number_of_routes = 100;
    double distance_between_rover = 2.0;
    double safe_distance_between_rover = 1.0;
    int number_of_obstacles = 4;
    double radius_of_obstacle = 1.0;
    int number_of_objectives = 10;
    
    //Create teams
    vector<population> teams;
    vector<population>* p_teams = &teams;
    for (int team_number = 0 ; team_number < pop_size; team_number++) {
        population p(number_of_rover, number_of_routes);
        p_teams->push_back(p);
    }
    
    //This is to make sure each agent starts at the location decided
    vector<vector<double>> coordinates_stat;
    vector<vector<double>>* p_coordinates_stat = &coordinates_stat;
    for (int rover = 0 ; rover <number_of_rover; rover++) {
        vector<double> temp;
        double temp_x_const = 2.0+(distance_between_rover*rover);
        double temp_y_const = 0.0;
        double temp_z_const = 0.0;
        temp.push_back(temp_x_const);
        temp.push_back(temp_y_const);
        temp.push_back(temp_z_const);
        coordinates_stat.push_back(temp);
        temp.clear();
    }
    
    //Obstacles
    vector<vector<double>> location_obstacle;
    vector<vector<double>>* p_location_obstacle = &location_obstacle;
    
    
    //data to store
    vector<vector<vector<vector<vector<double>>>>> coordinates_over_all;
    vector<vector<vector<vector<vector<double>>>>>* p_coordinates_over_all = &coordinates_over_all;
    vector<vector<vector<vector<double>>>> fitness_over_all;
    vector<vector<vector<vector<double>>>>* p_fitness_over_all = &fitness_over_all;
    
    
    int number_of_generations = 3000;
    
    
    for (int generation = 0 ; generation < number_of_generations; generation++) {
        //cout<<generation<<endl;
        create_team(p_teams, number_of_rover, number_of_routes,generation);
        save_team_numbers(p_teams,generation,number_of_rover,number_of_routes);
        initial_team(p_teams, p_location_obstacle,number_of_obstacles,p_coordinates_stat, distance_between_rover);
        simulation_team(p_teams, p_location_obstacle, generation,number_of_obstacles,p_coordinates_stat, distance_between_rover,number_of_routes,number_of_rover);
        distance_team(p_teams, distance_between_rover, safe_distance_between_rover, radius_of_obstacle, p_location_obstacle,number_of_objectives);
        normalization(p_teams, number_of_objectives);
        
        print_values_to_file(generation, p_teams, number_of_generations);
//        if (generation == 0) {
//            print_values_to_file(generation, p_teams);
//        }else if (generation%100 == 0 ){
//            print_values_to_file(generation, p_teams);
//        }else if (generation == number_of_generations-1){
//            print_values_to_file(generation, p_teams);
//        }
        int method_used = 3;
        switch (method_used) {
            case 0:
                ea(p_teams);
                break;
            case 1:
                nsga_ii(p_teams,number_of_objectives,generation);
                break;
            case 2:
                nsga_iii(p_teams,number_of_objectives,generation);
                break;
            case 3:
                hof(p_teams, number_of_objectives, generation);
                break;
            default:
                break;
        }
        
        clear_teams(p_teams);
        
    }

    
}

int main(int argc, const char * argv[]) {
    srand ( time(NULL) );
    cout<<"This is the current location 6"<<endl;
    //run_simulation_function();
    return 0;
}


