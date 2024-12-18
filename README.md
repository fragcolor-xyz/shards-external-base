# Creating External Shards for Shards Language

This repository serves as a template for creating external shards in the Shards programming language. It demonstrates the basic structure and best practices for implementing external functionality.

## Project Structure

```
.
├── CMakeLists.txt          # Build configuration
├── calculator.cpp          # Example shard implementation
└── README.md              # This file
```

## Key Components

### 1. CMakeLists.txt
- Defines project configuration and build settings
- Sets up necessary include paths
- Configures the shared library output
- Handles platform-specific settings

### 2. Implementation File (calculator.cpp)
- Contains the actual shard implementations
- Demonstrates how to create operations with:
  - Input/output type definitions
  - Parameter handling
  - State management
  - Resource initialization and cleanup
  - Error handling

## Creating Your Own Shard

1. **Setup Project Structure**
   - Copy this template
   - Rename the project in `CMakeLists.txt`
   - Create your implementation file

2. **Define Your Operations**
   - Create a namespace for your shard
   - Implement structs for each operation
   - Define input/output types
   - Add parameters if needed
   - Implement the `activate` method

3. **Register Your Shards**
   - Use `REGISTER_SHARD` in the `registerExternalShards` function
   - Follow the naming convention: "Namespace.Operation"

## Example Implementation

The template includes a simple calculator example with two operations:

1. **Calculator.Add**
   - Accumulates input values
   - Demonstrates basic operation structure
   - Shows parameter handling

2. **Calculator.Memory**
   - Implements memory operations (store/recall/clear)
   - Shows more complex state management
   - Demonstrates parameter-based behavior

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Best Practices

1. **Type Safety**
   - Always check input types
   - Throw appropriate errors for invalid inputs
   - Use clear error messages

2. **Resource Management**
   - Initialize resources in `warmup`
   - Clean up in `cleanup`
   - Handle memory carefully

3. **Error Handling**
   - Use `ActivationError` for runtime errors
   - Provide clear error messages
   - Validate inputs and parameters

4. **Documentation**
   - Comment your code
   - Provide clear parameter descriptions
   - Document any special requirements

## Integration

To use your shard in a Shards project:

1. Build the shared library
2. Create an `externals` folder in the same directory as your Shards script
3. Place the built library in the `externals` folder
4. The Shards runtime will automatically load the external shard

Example usage in Shards:

```shards
# Using the calculator operations
Calculator.Add(5)    # Add 5 to accumulator
Calculator.Memory("store")    # Store current value
Calculator.Memory("recall")   # Recall stored value
```

Project structure example:
```
your_project/
├── your_script.shs     # Your Shards script
└── externals/            # External shards folder
    └── calculator        # The built library
``` 
