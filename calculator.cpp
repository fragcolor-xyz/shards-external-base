/* Example External Shard for Shards Language
 * This is a template showing how to create an external shard
 */

#include <shards/dllshard.hpp>
#include <shards/shards.hpp>

using namespace shards;

namespace Calculator {

// Example of a simple calculator operation (Addition)
struct Add {
    // Define input and output types
    static SHTypesInfo inputTypes() { return CoreInfo::FloatType; }
    static SHTypesInfo outputTypes() { return CoreInfo::FloatType; }

    // Optional: Define parameters if your operation needs configuration
    static inline Parameters Params{
        {"Description",
         "Optional description of what this operation does"_optional,
         {CoreInfo::StringType}}
    };
    static SHParametersInfo parameters() { return Params; }

    // State variables (if needed)
    float accumulator = 0.0f;
    std::string description;

    // Parameter handling
    void setParam(int index, SHVar value) {
        if (index == 0) {
            description = std::string(value.payload.stringValue, value.payload.stringLen);
        }
    }

    SHVar getParam(int index) {
        if (index == 0) {
            return Var{description};
        }
        return Var{};
    }

    // Optional: Initialization code
    void warmup(SHContext* context) {
        // Initialize any resources needed
        accumulator = 0.0f;
    }

    // Optional: Cleanup code
    void cleanup() {
        // Clean up any resources
    }

    // Main operation implementation
    SHVar activate(SHContext* context, const SHVar& input) {
        if (input.valueType != SHType::Float) {
            throw ActivationError("Calculator.Add requires float input");
        }
        
        accumulator += input.payload.floatValue;
        return Var{accumulator};
    }
};

// Example of a more complex operation (Memory)
struct Memory {
    static SHTypesInfo inputTypes() { return CoreInfo::FloatType; }
    static SHTypesInfo outputTypes() { return CoreInfo::FloatType; }

    static inline Parameters Params{
        {"Operation",
         "Operation to perform: 'store', 'recall', or 'clear'"_optional,
         {CoreInfo::StringType}}
    };
    static SHParametersInfo parameters() { return Params; }

    std::string operation = "recall";
    float memory = 0.0f;

    void setParam(int index, SHVar value) {
        if (index == 0) {
            operation = std::string(value.payload.stringValue, value.payload.stringLen);
        }
    }

    SHVar getParam(int index) {
        if (index == 0) {
            return Var{operation};
        }
        return Var{};
    }

    SHVar activate(SHContext* context, const SHVar& input) {
        if (operation == "store") {
            memory = input.payload.floatValue;
            return input;
        } else if (operation == "clear") {
            memory = 0.0f;
            return Var{memory};
        } else { // recall
            return Var{memory};
        }
    }
};

} // namespace Calculator

// Register the external shards
namespace shards {
void registerExternalShards() {
    // Register each operation in your shard
    REGISTER_SHARD("Calculator.Add", Calculator::Add);
    REGISTER_SHARD("Calculator.Memory", Calculator::Memory);
}
} // namespace shards 