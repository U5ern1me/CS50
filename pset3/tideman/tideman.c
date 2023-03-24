#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check(int i, int j);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(name , candidates[i]) == 0) // If name of canditate matches user entry of candidate's name
        {
            ranks[rank] = i;
            return true;
        }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
        for (int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int count = -1; // To keep count of number of pairs[] elements
    for (int i = 0; i < candidate_count; i++)
        for (int j = i + 1; j < candidate_count; j++)
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i]) // If i is preferred over j
                    pairs[++count].winner = i;
                else // If j is preferred over i
                    pairs[++count].winner = j;
                pairs[count].loser = i + j - pairs[count].winner;
            }
    pair_count = count + 1;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int edge[pair_count]; // To store edge a winner has over a loser in each pairs[] element
    for (int i = 0; i < pair_count; i++)
        edge[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    for (int j = pair_count - 1; j > 0; j--) // Bubble sorting pairs[] in decreasing order of edge winner has over loser
        for (int k = 0; k < j; k++)
            if (edge[k] < edge[k + 1])
            {
                edge[k + 1] = edge[k + 1] + edge[k];
                edge[k]     = edge[k + 1] - edge[k];
                edge[k + 1] = edge[k + 1] - edge[k];
                
                pairs[k + 1].winner = pairs[k + 1].winner + pairs[k].winner;
                pairs[k].winner     = pairs[k + 1].winner - pairs[k].winner;
                pairs[k + 1].winner = pairs[k + 1].winner - pairs[k].winner;
                
                pairs[k + 1].loser = pairs[k + 1].loser + pairs[k].loser;
                pairs[k].loser     = pairs[k + 1].loser - pairs[k].loser;
                pairs[k + 1].loser = pairs[k + 1].loser - pairs[k].loser;
            }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
        if (check(pairs[i].winner, pairs[i].loser)) // Checks if edge does not create a loop
            locked[pairs[i].winner][pairs[i].loser] = true;
}

// Check if i to j pair can be locked in graph
bool check(int i, int j) // Recursive function
{
    if (i != j)
    {
        for (int c = 0; c < candidate_count; c++)
            if (locked[c][i]) // If c to i pair has been locked in graph
                if (!check(c, j)) // If c to j pair can't be locked in graph, i to j pair can't be locked in too.
                    return false;
        return true;
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    int flag = 0; // Serves as indicator to find out source of graph
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
            if (locked[j][i] == true)
                flag ++;
        if (flag == 0) // If locked[j][i] is false for all values of j for a particular i, i.e if i is source
            printf("%s\n", candidates[i]);
        flag = 0;
    }
}