//
// Created by George Thiruvathukal on 2/17/24.
//

#include <gtest/gtest.h>

#include "int_stack.hh"

TEST(IntStackTests, Initialization)
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    ASSERT_EQ(int_stack_capacity(&stack1), 10);
}

TEST(IntStackTests, PushToCapacityAndOverflow)
{
    // create stack that can hold 10 items
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // ensure it's full
    ASSERT_EQ(int_stack_size(&stack1), capacity);

    // try to add one more
    int result = int_stack_push(&stack1, capacity+1);

    // and make sure it is an overflow (error)
    ASSERT_FALSE(result);
}


TEST(IntStackTests, PushToCapcacityPopUntilUnderflow
)
{
    // create stack that can hold 10 items [similar to previous test]
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // now drain it one item at a time, ensuring each item is the value expected
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }

    // try to remove from empty stack and ensure it fails
    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, Dup) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 42);
    ASSERT_TRUE(int_stack_dup(&stack));
    ASSERT_EQ(int_stack_size(&stack), 2);

    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 42);

    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 42);
}

TEST(IntStackTests, Swap) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 1);
    int_stack_push(&stack, 2);
    ASSERT_TRUE(int_stack_swap(&stack));

    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 1);

    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 2);
}

TEST(IntStackTests, Over) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 10);
    int_stack_push(&stack, 20);
    ASSERT_TRUE(int_stack_over(&stack));
    ASSERT_EQ(int_stack_size(&stack), 3);

    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 20);
}

TEST(IntStackTests, Rot) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 1);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 3);
    ASSERT_TRUE(int_stack_rot(&stack));

    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 2);

    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 3);

    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 1);
}

TEST(IntStackTests, TwoDup) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 1);
    int_stack_push(&stack, 2);
    ASSERT_TRUE(int_stack_2dup(&stack));
    ASSERT_EQ(int_stack_size(&stack), 4);

    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 2); // first duplicate

    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 1); // second duplicate
}

TEST(IntStackTests, Add) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 5);
    int_stack_push(&stack, 7);
    ASSERT_TRUE(int_stack_add(&stack)); 
    ASSERT_EQ(int_stack_size(&stack), 1);

    int result;
    int_stack_pop(&stack, &result);
    ASSERT_EQ(result, 12);
}

TEST(IntStackTests, Subtract) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 10);
    int_stack_push(&stack, 5);
    ASSERT_TRUE(int_stack_subtract(&stack)); 
    ASSERT_EQ(int_stack_size(&stack), 1);

    int result;
    int_stack_pop(&stack, &result);
    ASSERT_EQ(result, 5);
}

TEST(IntStackTests, Multiply) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 4);
    int_stack_push(&stack, 5);
    ASSERT_TRUE(int_stack_multiply(&stack)); 
    ASSERT_EQ(int_stack_size(&stack), 1);

    int result;
    int_stack_pop(&stack, &result);
    ASSERT_EQ(result, 20);
}

TEST(IntStackTests, Divide) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 20);
    int_stack_push(&stack, 5);
    ASSERT_TRUE(int_stack_divide(&stack)); 
    ASSERT_EQ(int_stack_size(&stack), 1);

    int result;
    int_stack_pop(&stack, &result);
    ASSERT_EQ(result, 4);
}

TEST(IntStackTests, DivideByZero) {
    int_stack_t stack;
    int_stack_init(&stack, 10);

    int_stack_push(&stack, 20);
    int_stack_push(&stack, 0); // divide by zero Should fail
    ASSERT_FALSE(int_stack_divide(&stack)); 
    ASSERT_EQ(int_stack_size(&stack), 2); // Stack size remains unchanged

    // Optionally, verify the stack's integrity remains intact
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 0);

    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 20);
}



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
