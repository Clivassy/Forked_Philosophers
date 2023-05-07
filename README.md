<h1 align="center">Forked_Philosophers</h1>

# Overview
This is a C implementation of the Dining Philosophers problem, which is a classic example of a concurrency problem. <br>
The problem involves a group of philosophers who are seated at a circular table with a fork between each pair of adjacent philosophers. <br>
Each philosopher alternates between thinking and eating, and to eat, they must pick up the two forks on either side of them.<br>
However, since there are only as many forks as there are philosophers, deadlock can occur if each philosopher picks up one fork and waits for the other.

# Getting Started
This program simulates the behavior of the philosophers using threads and mutexes to avoid deadlock. <br>
The program takes the following command-line arguments:<br>
`` ./philo num_philosophers time_to_die time_to_eat time_to_sleep [num_times_each_philosopher_must_eat] `` <br>

num_philosophers: the number of philosophers at the table<br>
time_to_die: the time in milliseconds after which a philosopher dies if they have not started eating<br>
time_to_eat: the time in milliseconds it takes for a philosopher to eat<br>
time_to_sleep: the time in milliseconds it takes for a philosopher to sleep<br>
num_times_each_philosopher_must_eat (optional): the number of times each philosopher must eat before the simulation ends<br>
The output of the program is a log of the actions of each philosopher, along with a timestamp in milliseconds.<br>

## Prerequisites

## Installation

``git clone git@github.com:Clivassy/Forked_Philosophers.git``<br>
``cd Forked_Philosophers``<br>
``make``<br>

## Usage

To compile the program, run make. This will create an executable called philo. <br>
To run the program, pass in the desired command-line arguments: <br>
``./philo 5 800 200 200``
This will simulate a table with 5 philosophers, where each philosopher dies after 800 milliseconds of inactivity, it takes 200 milliseconds to eat and sleep.<br>
Optionally, you can specify the number of times each philosopher must eat before the simulation ends: <br>
``./philo 5 800 200 200 3``<br>

This will end the simulation after each philosopher has eaten 3 times. <br>

## Useful Ressources 
The Dining Philosophers Problem : <br>
<https://www.youtube.com/watch?v=FYUi-u7UWgw> <br>
<https://www.youtube.com/watch?v=NbwbQQB7xNQ> <br><br> 
Threads : <br>
<https://www.youtube.com/watch?v=o_GbRujGCnM> <br>
<https://www.tutorialspoint.com/multithreading-in-c> <br>
<https://www.geeksforgeeks.org/multithreading-c-2/> <br>
<br>
Datas Race: <br>
<https://www.youtube.com/watch?v=oq29KUy29iQ&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=4>
