# Relative Path
### Equivalent to the [getrelativepath from c#](https://docs.microsoft.com/en-us/dotnet/api/system.io.path.getrelativepath?view=net-5.0)


Finds path from one directory to another directory. See [dotNet documentation to see more](https://docs.microsoft.com/en-us/dotnet/api/system.io.path.getrelativepath?view=net-5.0)   
## Usage:
1. First input is the path to the directory to start with
2. Second input is the path from any directory that exists in the path in the first path to find the last directory
3. The output will be a path that we need to go to get from First Input Directory to the Secodn Input Directory

## Example:
* First input(path to start with) - `./aa/././bb/./cc`    
* Second input(path to find the directory) - `aa/cc/dd`   
* *Result* - `../../cc/`
 
