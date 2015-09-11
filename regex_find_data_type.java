import java.util.*;
import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class pattern{
  public static void print(String str){
    //function to print in correct order
    char convert[] = str.toCharArray();
    //the string converted to char array
    int a, mul = 0, mul1 = 0;
    for(a = 0;a < (str.length()) - 3;a++){
      if(convert[a] == 'i' && convert[a + 1] == 'n' && convert[a + 2] == 't'){
        String s = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).toString();
        //make "int" in front of every variable for pattern matching
        System.out.println(" : " + s);
      }
      else if(convert[a] == 'f' && convert[a + 1] == 'l' && convert[a + 2] == 'o' && convert[a + 3] == 'a' && convert[a + 4] == 't'){
        String s = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).append(convert[a + 3]).append(convert[a + 4]).toString();
        //make "float" in front of every variable for pattern matching
        System.out.println(" : " + s);
      }
      else if(convert[a] == 'S' && convert[a + 1] == 't' && convert[a + 2] == 'r' && convert[a + 3] == 'i' && convert[a + 4] == 'n' && convert[a + 5] == 'g'){
        //make "String" in front of every variable for pattern matching
        mul++;
        String s = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).append(convert[a + 3]).append(convert[a + 4]).append(convert[a + 5]).toString();
        if(mul < 2){
          System.out.println(" : " + s);
          //not print if String a = new String() type, print only one time
        }
      }
      else if(convert[a] == 'd' && convert[a + 1] == 'o' && convert[a + 2] == 'u' && convert[a + 3] == 'b' && convert[a + 4] == 'l' && convert[a + 5] == 'e'){
        //make "double" in front of every variable for pattern matching
        String s = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).append(convert[a + 3]).append(convert[a + 4]).append(convert[a + 5]).toString();
        System.out.println(" : " + s);
      }
    }
  }

  public static void main(String[] args){
    int i, j, k, flag = 0, c = -1, c1 = 0, token = 0, token1 = 0, flag1 = 0, c2 = 0, flag2 = 0;
    //memory allocation
    int count[] = new int[10];
    int count1[] = new int[10];
    for(i = 0;i < 10;i++){
      count[i] = 0;
    }
    //list of strings to store the strings
    List<String> strings = new ArrayList<String>();
    try{
    //read the .java file using the scanner class
      File file = new File("program.java");
      Scanner scanner = new Scanner(file);
      //Scanner class object to scan every line in the .java file and print or store it somewhere, i.e. here in the list of strings
      while(scanner.hasNextLine()){
        //iterate till next line
        strings.add(scanner.nextLine());
      }
    }
    catch(Exception e){
    //report Exception
      System.out.println("File Does Not Exist !");
    }
    //iterate through the string
    Iterator<String> myiterator = strings.iterator();
    System.out.println();
    //iterate till nextLine not NULL
    while(myiterator.hasNext()){
      c++;
      c1 = 0;
      flag = 0;
      String check = myiterator.next();
      //setting the next string iterating over to String variable check
      char array[] = check.toCharArray();
      //convert check to char array for finding cases
      for(i = 0;i < (check.length()) - 1;i++){
        //case when variables separated by different data types
        if(array[i] == ';'){
          count[c]++;
          if(count[c] > 1){
            break;
            //break if muliple semicolons found...because all are handled at one time
          }
          flag = 1;
          //StringTokenizer to tokenize about the semicolons
          StringTokenizer st = new StringTokenizer(check, ";");
          while(st.hasMoreTokens()){
            //iterate till has more tokens
            String tempstr = st.nextToken();
            //pattern class and its static method to compile the patter
            Pattern p12 = Pattern.compile("(?:(?:int|float|String|double)(?:\\s+)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*)|(?<=\\G,)(?:\\s*)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*))");
            //matcher class and its object's function to match the pattern with the input string(which is in iteration)
            Matcher m12 = p12.matcher(tempstr);
            if(m12.find()){
              //if found, then print in groups along with variables and data types
              System.out.print("Variable Name(s) -> " + m12.group(1));
              print(tempstr);
              //print function call to print along with concatenation and string building to print in the format : variable -> data-type
              System.out.println();
            }
          }
        }
        //following if-else block to print the data types of the arguments provided in the function(if you want)
        else if(array[i] == '('){
          flag = 1;
          //mark the flag 1 as no need to find patterns in the same string again
          StringTokenizer st1 = new StringTokenizer(check, "(");
          //tokenize the string about "("
          while(st1.hasMoreTokens()){
            String tempstr1 = st1.nextToken();
            //iterate till has next token
            char array3[] = tempstr1.toCharArray();
            //convert the tempstr to char array for indexing
            for(k = 0;k < (tempstr1.length()) - 1;k++){
              if(array3[k] == ','){
                //case if muliple data types as arguments given in the function header
                StringTokenizer st0 = new StringTokenizer(tempstr1, ",");
                while(st0.hasMoreTokens()){
                  //iterate till has moretokens
                  String breaker = st0.nextToken();
                  //equate the token to breaker string
                  Pattern p01 = Pattern.compile("(?:(?:int|float|String|double)(?:\\s+)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*)|(?<=\\G,)(?:\\s*)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*))");
                  //compile the regex with the input and string match using the matcher() method
                  Matcher m01 = p01.matcher(breaker);
                  if(m01.find()){
                    //print in groups if match found
                    System.out.print("Variable Name(s) -> " + m01.group(1));
                    print(breaker);
                    System.out.println();
                  }
                }
              }
            }
          }
        }
        else if(array[i] == '='){
          flag1 = 0;
          //case when if of more equations in the line
          c1++;
          //increment count1 corresponding to fixed line : c1 which increments only aftr iterating to next line in .java file for similar case(= case)
          if(c1 == 1){
            flag = 1;
            //now dont proceed to end pattern amd matching for simple case to avoid duplicacy
            for(j = i + 1;j < (check.length()) - 1;j++){
              if(array[j] == ','){
                flag1 = -1;
              }
            }
            if(flag1 == -1){
              //proceed condition satisfied
              String s1 = "";
              char convert[] = check.toCharArray();
              //convert the string into array and apply respective data types to each of the following variable
              int a;
              for(a = 0;a < (check.length()) - 3;a++){
                if(convert[a] == 'i' && convert[a + 1] == 'n' && convert[a + 2] == 't'){
                  //make int
                  s1 = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).toString();
                  break;
                  //break from the loop since we need only one data-type(in the starting of the line, so avoid matching with other strings)
                }
                else if(convert[a] == 'f' && convert[a + 1] == 'l' && convert[a + 2] == 'o' && convert[a + 3] == 'a' && convert[a + 4] == 't'){
                  //make float
                  s1 = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).append(convert[a + 3]).append(convert[a + 4]).toString();
                  //break from the loop since we need only one data-type(in the starting of the line, so avoid matching with other strings)
                  break;
                }
                else if(convert[a] == 'S' && convert[a + 1] == 't' && convert[a + 2] == 'r' && convert[a + 3] == 'i' && convert[a + 4] == 'n' && convert[a + 5] == 'g'){
                  //make String
                  s1 = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).append(convert[a + 3]).append(convert[a + 4]).append(convert[a + 5]).toString();
                  //break from the loop since we need only one data-type(in the starting of the line, so avoid matching with other strings)
                  break;
                }
                else if(convert[a] == 'd' && convert[a + 1] == 'o' && convert[a + 2] == 'u' && convert[a + 3] == 'b' && convert[a + 4] == 'l' && convert[a + 5] == 'e'){
                  //make double
                  s1 = new StringBuilder().append(convert[a]).append(convert[a + 1]).append(convert[a + 2]).append(convert[a + 3]).append(convert[a + 4]).append(convert[a + 5]).toString();
                  //break from the loop since we need only one data-type(in the starting of the line, so avoid matching with other strings)
                  break;
                }
              }
              StringTokenizer st2 = new StringTokenizer(check, ",");
              token1 = 0;
              //tokenize the string about ; to split into different variables and then proceed till has more tokens
              while(st2.hasMoreTokens()){
                token1++;
                //increment token1 to 1
                String tempstr2 = st2.nextToken();
                if(token1 > 1){
                  //concatenate only for rest variables : like in int a, b, c: concatenate only for b and c
                  tempstr2 = s1.concat(tempstr2);
                }
                //pattern class and its static method to compile the patter
                Pattern p13 = Pattern.compile("(?:(?:int|float|String|double)(?:\\s+)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*)|(?<=\\G,)(?:\\s*)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*))(?=,|\\)|=)");
                //matcher class and its object's function to match the pattern with the input string(which is in iteration)
                Matcher m13 = p13.matcher(tempstr2);
                if(m13.find()){
                  //if found, print the variables and data types
                  System.out.print("Variable Name(s) -> " + m13.group(1));
                  String output = tempstr2.substring(m13.start(),m13.end()).trim();
                  //print function called in order to print in correct manner : variable -> data-type
                  print(output);
                  System.out.println();
                }
              }
            }
          }
        }
        //else block if none of the above cases are followed
        else{
          ;
        }
      }
      if(flag != 1){
        //proceed to this block only if previous cases are not followed...i.e. simple cases
        Pattern p = Pattern.compile("(?:(?:int|float|String|double)(?:\\s+)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*)|(?<=\\G,)(?:\\s*)([a-zA-Z_,\\s][a-zA-Z_0-9,\\s]*)(?:\\s*))(?=,|;|=)");
        //pattern class and its static method to compile the patter
        Matcher m = p.matcher(check);
        //matcher class and its object's function to match the pattern with the input string(which is in iteration)
        if(m.find()){
          //if found, print the variables and data types
          System.out.print("Variable Name(s) -> " + m.group(1));
          String output = check.substring(m.start(),m.end()).trim();
          //print function called in order to print in correct manner : variable -> data-type
          print(output);
          System.out.println();
        }
      }
    }
  }
}
