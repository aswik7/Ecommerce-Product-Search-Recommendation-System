
# Product Recommendation System

## Description

A Product Recommendation System suggests relevant products to users based on their interests, previous activities, purchase history, product popularity, and ratings. It helps users discover products that best match their preferences.

## Features

- View all available products.
- Search for products using their ID.
- Get personalized product recommendations.
- Filter recommendations by category.
- Display top recommended products based on recommendation scores.

## Concepts Used

- C++ Programming
- Arrays and Structures
- Linear Search
- Max Heap
- Recommendation Scoring
- Time Complexity Analysis

## How It Works

The system calculates a recommendation score for each eligible product using three factors:

1. **User Preference:** Based on the user's interactions with products in the same category.
2. **Product Popularity:** Based on how users interact with a product.
3. **Product Rating:** Based on the product's rating.

A Max Heap is used to retrieve products with the highest recommendation scores.

## Technologies Used

- C++
