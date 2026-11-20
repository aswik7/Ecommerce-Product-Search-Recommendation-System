
#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUCTS = 10;
const int MAX_INTERACTIONS = 30;

struct Product
{
    int id;
    string name;
    string category;
    float rating;
};

struct Interaction
{
    int userId;
    int productIndex;
    string action;
};

struct Recommendation
{
    int productIndex;
    int score;
};

Product products[MAX_PRODUCTS] =
{
    {101, "The Art of Communication", "Self Development", 4.8f},
    {102, "Introduction to Programming", "Technology", 4.7f},
    {103, "The Power of Habit", "Self Development", 4.5f},
    {104, "Basics of Financial Management", "Finance", 4.4f},
    {105, "Learning Python Programming", "Technology", 4.3f},
    {106, "Personal Finance for Beginners", "Finance", 4.9f}
};

int productCount = 6;

Interaction interactions[MAX_INTERACTIONS] =
{
    {101, 0, "Purchase"},
    {101, 1, "View"},
    {102, 0, "Purchase"},
    {102, 2, "Purchase"},
    {102, 4, "Cart"},
    {102, 5, "Purchase"},
    {103, 1, "Purchase"},
    {103, 2, "Cart"},
    {103, 3, "Purchase"},
    {103, 5, "Cart"},
    {104, 4, "Purchase"},
    {104, 5, "Purchase"},
    {104, 2, "View"}
};

int interactionCount = 13;

// Assign weights to user activities
int getWeight(string action)
{
    if (action == "View")
        return 1;

    if (action == "Cart")
        return 2;

    if (action == "Purchase")
        return 3;

    return 0;
}

// Search product using its ID
int searchProduct(int id)
{
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
            return i;
    }

    return -1;
}

bool hasInteracted(int userId, int productId)
{
    for (int i = 0; i < interactionCount; i++)
    {
        int index = interactions[i].productIndex;

        if (interactions[i].userId == userId &&
            products[index].id == productId &&
            interactions[i].action == "Purchase")
        {
            return true;
        }
    }

    return false;
}

// Calculate recommendation score
int calculateScore(int userId, int productIndex)
{
    int preferenceScore = 0;
    int popularityScore = 0;

    for (int i = 0; i < interactionCount; i++)
    {
        int index = interactions[i].productIndex;

        if (interactions[i].userId == userId)
        {
            if (products[index].category ==
                products[productIndex].category)
            {
                preferenceScore += getWeight(interactions[i].action);
            }
        }
    }

    for (int i = 0; i < interactionCount; i++)
    {
        if (interactions[i].productIndex == productIndex)
        {
            popularityScore += getWeight(interactions[i].action);
        }
    }

    int ratingScore = (int)(products[productIndex].rating * 2);

    return (preferenceScore * 10) + popularityScore + ratingScore;
}

// Max Heap
class MaxHeap
{
    Recommendation heap[MAX_PRODUCTS];
    int size;

public:

    MaxHeap()
    {
        size = 0;
    }

    void insert(int productIndex, int score)
    {
        int i = size;

        heap[i].productIndex = productIndex;
        heap[i].score = score;

        size++;

        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (heap[parent].score < heap[i].score)
            {
                Recommendation temp = heap[parent];
                heap[parent] = heap[i];
                heap[i] = temp;

                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    Recommendation extractMax()
    {
        Recommendation result = heap[0];

        heap[0] = heap[size - 1];
        size--;

        int i = 0;

        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < size && heap[left].score > heap[largest].score)
                largest = left;

            if (right < size && heap[right].score > heap[largest].score)
                largest = right;

            if (largest != i)
            {
                Recommendation temp = heap[i];
                heap[i] = heap[largest];
                heap[largest] = temp;

                i = largest;
            }
            else
            {
                break;
            }
        }

        return result;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

void displayProducts()
{
    cout << "\nProduct Catalogue\n";

    for (int i = 0; i < productCount; i++)
    {
        cout << "\nID: " << products[i].id;
        cout << "\nName: " << products[i].name;
        cout << "\nCategory: " << products[i].category;
        cout << "\nRating: " << products[i].rating << endl;
    }
}

string selectCategory()
{
    int choice;

    cout << "\nSelect Category\n";
    cout << "0. All Categories\n";
    cout << "1. Self Development\n";
    cout << "2. Technology\n";
    cout << "3. Finance\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            return "Self Development";

        case 2:
            return "Technology";

        case 3:
            return "Finance";

        default:
            return "All";
    }
}

// Generate Top-K recommendations
void generateRecommendations(int userId, int k, string category)
{
    MaxHeap maxHeap;
    int available = 0;

    for (int i = 0; i < productCount; i++)
    {
        if (hasInteracted(userId, products[i].id))
            continue;

        if (category != "All" && products[i].category != category)
            continue;

        int score = calculateScore(userId, i);

        maxHeap.insert(i, score);
        available++;
    }

    if (available == 0)
    {
        cout << "\nNo recommendations available.\n";
        return;
    }

    if (k > available)
        k = available;

    cout << "\nTop " << k << " Recommended Products\n";

    for (int i = 0; i < k; i++)
    {
        Recommendation result = maxHeap.extractMax();

        int index = result.productIndex;

        cout << "\nRank: " << i + 1;
        cout << "\nProduct ID: " << products[index].id;
        cout << "\nName: " << products[index].name;
        cout << "\nCategory: " << products[index].category;
        cout << "\nRating: " << products[index].rating;
        cout << "\nScore: " << result.score << endl;
    }
}

int main()
{
    int choice;

    cout << "Product Recommendation System\n";

    do
    {
        cout << "\n1. View All Products\n";
        cout << "2. Search Product\n";
        cout << "3. Get Recommendations\n";
        cout << "4. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                displayProducts();
                break;
            }

            case 2:
            {
                int id;

                cout << "Enter Product ID: ";
                cin >> id;

                int index = searchProduct(id);

                if (index != -1)
                {
                    cout << "\nProduct Found\n";
                    cout << "Name: " << products[index].name << endl;
                    cout << "Category: " << products[index].category << endl;
                    cout << "Rating: " << products[index].rating << endl;
                }
                else
                {
                    cout << "\nProduct Not Found\n";
                }

                break;
            }

            case 3:
            {
                int userId, k;

                cout << "Enter User ID (101-104): ";
                cin >> userId;

                string category = selectCategory();

                cout << "Enter number of recommendations: ";
                cin >> k;

                if (k <= 0)
                {
                    cout << "Enter a valid number.\n";
                    break;
                }

                generateRecommendations(userId, k, category);

                break;
            }

            case 4:
            {
                cout << "Thank you!\n";
                break;
            }

            default:
            {
                cout << "Invalid choice.\n";
            }
        }

    } while (choice != 4);

    return 0;
}
