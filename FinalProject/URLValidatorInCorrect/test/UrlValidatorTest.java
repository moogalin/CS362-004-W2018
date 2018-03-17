

import java.util.*;
import junit.framework.TestCase;


//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   public void testManualTest1() {
	   /* 
	    * Assert 
	    * http://www.google.com 
	    * is valid */
	   String[] schemes = {"http", "https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
	   String url = "http://www.google.com";
	   boolean isValid = true;  
	   assertEquals(url, isValid, urlValidator.isValid(url));
   }
   
   public void testManualTest2() {
	   /* 
	    * Assert 
	    * https://www.google.com 
	    * is valid 
	    * */
	   String[] schemes = {"http", "https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
	   String url = "https://www.google.com";
	   boolean isValid = true;  
	   assertEquals(url, isValid, urlValidator.isValid(url));
   }   
   
   public void testManualTest3() {
	   /* 
	    * Assert 
	    * https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%2frc%2fdesktops%2f102 
	    * is valid 
	    * */ 
	   String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
       String url = "https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%2frc%2fdesktops%2f102";
       boolean isValid = true;
       assertEquals(url, isValid, urlValidator.isValid(url));
   }
   
   public void testManualTest4() {
	   /* 
	    * Assert 
	    * https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%2frc%2fdesktops%2f102 
	    * is valid 
	    * */ 
	   String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
       String url = "https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%2frc%2fdesktops%2f102";
       boolean isValid = true;
       assertEquals(url, isValid, urlValidator.isValid(url));
   }
   
   public void testManualTest5()
   {
	   /* 
	    * Assert 
	    * ht://www.google.com 
	    * is invalid 
	    * */ 
	   String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
       String url = "ht://www.google.com";
       boolean isValid = false;
       assertEquals(url, isValid, urlValidator.isValid(url));
   }
   
   public void testManualTest6()
   {
	   /* 
	    * Assert 
	    * (blank)
	    * is invalid 
	    * */ 
	   String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
       String url = "";
       boolean isValid = false;
       assertEquals(url, isValid, urlValidator.isValid(url));
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
