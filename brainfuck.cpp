#include "brainfuck.hpp"

Brainfuck::Brainfuck() : tape(1000, 0), pointer(0) {
}

void Brainfuck::do_move_right() {
    pointer++;
    if (pointer >= tape.size()) {
        tape.resize(tape.size() * 2, 0);
    }
}

void Brainfuck::do_move_left() {
    if (pointer > 0) {
        pointer--;
    }
}

void Brainfuck::do_increment() {
    tape[pointer]++;
}

void Brainfuck::do_decrement() {
    tape[pointer]--;
}

void Brainfuck::do_output() {
    std::cout << static_cast<char>(tape[pointer]);
    std::cout.flush();
}

void Brainfuck::do_input() {
    char c;
    if (std::cin.get(c)) {
        tape[pointer] = static_cast<int>(static_cast<unsigned char>(c));
    } else {
        tape[pointer] = 0;
    }
}

BrainfuckProxy Brainfuck::operator++() {
    return BrainfuckProxy(this, OpType::MoveRight);
}

BrainfuckProxy Brainfuck::operator--() {
    return BrainfuckProxy(this, OpType::MoveLeft);
}

BrainfuckProxy Brainfuck::operator+() {
    return BrainfuckProxy(this, OpType::Increment);
}

BrainfuckProxy Brainfuck::operator-() {
    return BrainfuckProxy(this, OpType::Decrement);
}

BrainfuckProxy Brainfuck::operator!() {
    return BrainfuckProxy(this, OpType::Output);
}

BrainfuckProxy Brainfuck::operator*() {
    return BrainfuckProxy(this, OpType::Input);
}

BrainfuckProxy Brainfuck::operator&() {
    return BrainfuckProxy(this, OpType::LoopStart);
}

BrainfuckProxy Brainfuck::operator~() {
    return BrainfuckProxy(this, OpType::LoopEnd);
}

BrainfuckProxy::BrainfuckProxy(Brainfuck* b, OpType type) 
    : bf(b), executed(false), used_for_chain(false) {
    ops.push_back(type);
}

BrainfuckProxy BrainfuckProxy::operator++() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::MoveRight);
    return result;
}

BrainfuckProxy BrainfuckProxy::operator--() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::MoveLeft);
    return result;
}

BrainfuckProxy BrainfuckProxy::operator+() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::Increment);
    return result;
}

BrainfuckProxy BrainfuckProxy::operator-() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::Decrement);
    return result;
}

BrainfuckProxy BrainfuckProxy::operator!() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::Output);
    return result;
}

BrainfuckProxy BrainfuckProxy::operator*() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::Input);
    return result;
}

BrainfuckProxy BrainfuckProxy::operator&() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::LoopStart);
    return result;
}

BrainfuckProxy BrainfuckProxy::operator~() {
    BrainfuckProxy result(*this);
    result.executed = false;
    result.ops.push_back(OpType::LoopEnd);
    return result;
}

void BrainfuckProxy::execute() const {
    if (executed || ops.empty()) return;
    executed = true;
    
    std::vector<OpType> ops_reversed(ops.rbegin(), ops.rend());
    
    size_t pc = 0;
    std::stack<size_t> loop_stack;
    
    while (pc < ops_reversed.size()) {
        OpType op = ops_reversed[pc];
        
        if (op == OpType::LoopStart) {
            if (bf->tape[bf->pointer] == 0) {
                int depth = 1;
                size_t search_pc = pc + 1;
                while (depth > 0 && search_pc < ops_reversed.size()) {
                    if (ops_reversed[search_pc] == OpType::LoopStart) depth++;
                    else if (ops_reversed[search_pc] == OpType::LoopEnd) depth--;
                    search_pc++;
                }
                pc = search_pc;
                continue;
            } else {
                if (loop_stack.empty() || loop_stack.top() != pc) {
                    loop_stack.push(pc);
                }
                pc++;
            }
        }
        else if (op == OpType::LoopEnd) {
            if (bf->tape[bf->pointer] != 0 && !loop_stack.empty()) {
                pc = loop_stack.top();
                continue;
            } else {
                if (!loop_stack.empty()) loop_stack.pop();
                pc++;
            }
        }
        else {
            switch (op) {
                case OpType::MoveRight:
                    bf->do_move_right();
                    break;
                case OpType::MoveLeft:
                    bf->do_move_left();
                    break;
                case OpType::Increment:
                    bf->do_increment();
                    break;
                case OpType::Decrement:
                    bf->do_decrement();
                    break;
                case OpType::Output:
                    bf->do_output();
                    break;
                case OpType::Input:
                    bf->do_input();
                    break;
                default:
                    break;
            }
            pc++;
        }
    }
}

BrainfuckProxy::~BrainfuckProxy() {
    if (!used_for_chain) {
        execute();
    }
}
