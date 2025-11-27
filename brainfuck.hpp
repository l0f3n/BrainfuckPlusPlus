#pragma once

#include <iostream>
#include <vector>
#include <stack>

class Brainfuck;

enum class OpType {
    MoveRight,
    MoveLeft,
    Increment,
    Decrement,
    Output,
    Input,
    LoopStart,
    LoopEnd
};

class BrainfuckProxy {
private:
    Brainfuck* bf;
    std::vector<OpType> ops;
    mutable bool executed;
    mutable bool used_for_chain;
    
    friend class Brainfuck;
    BrainfuckProxy(Brainfuck* b, OpType type);
    
    void execute() const;
    
public:
    BrainfuckProxy(const BrainfuckProxy& other) 
        : bf(other.bf), ops(other.ops), executed(false), used_for_chain(false) {
        other.used_for_chain = true;
    }
    
    BrainfuckProxy operator++(); // > (move right)
    BrainfuckProxy operator--(); // < (move left)
    BrainfuckProxy operator+();  // + (increment)
    BrainfuckProxy operator-();  // - (decrement)
    BrainfuckProxy operator!();  // . (output)
    BrainfuckProxy operator*();  // , (input)
    BrainfuckProxy operator&();  // [ (loop start)
    BrainfuckProxy operator~();  // ] (loop end)
    
    ~BrainfuckProxy();
};

class Brainfuck {
private:
    std::vector<int> tape;
    size_t pointer;
    std::stack<size_t> loop_stack;
    
    friend class BrainfuckProxy;

public:
    Brainfuck();
    BrainfuckProxy operator++(); // > (move right)
    BrainfuckProxy operator--(); // < (move left)
    BrainfuckProxy operator+();  // + (increment)
    BrainfuckProxy operator-();  // - (decrement)
    BrainfuckProxy operator!();  // . (output)
    BrainfuckProxy operator*();  // , (input)
    BrainfuckProxy operator&();  // [ (loop start)
    BrainfuckProxy operator~();  // ] (loop end)
    
    void do_increment();
    void do_decrement();
    void do_move_right();
    void do_move_left();
    void do_output();
    void do_input();
};

