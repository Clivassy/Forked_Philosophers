<h1 align="center">Forked_Philosophers</h1>

# Overview
This is a C implementation of the Dining Philosophers problem, which is a classic example of a concurrency problem. The problem involves a group of philosophers who are seated at a circular table with a fork between each pair of adjacent philosophers. Each philosopher alternates between thinking and eating, and to eat, they must pick up the two forks on either side of them. However, since there are only as many forks as there are philosophers, deadlock can occur if each philosopher picks up one fork and waits for the other.

This program simulates the behavior of the philosophers using threads and mutexes to avoid deadlock. The program takes the following command-line arguments:
`` ./philo num_philosophers time_to_die time_to_eat time_to_sleep [num_times_each_philosopher_must_eat] `` <br>

# Getting Started

## Prerequisites

## Installation

## Usage

## Code Structure

## Rules and Constraints

## Useful Ressources 
