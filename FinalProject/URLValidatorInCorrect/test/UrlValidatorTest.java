

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
	   /* 
	    * Assert 
	    * (blank)
	    * is invalid 
	    * */ 
       UrlValidator urlValidator = new UrlValidator();
       String url = "";
       boolean isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));

   }
   
   public void testYourSecondPartition(){
	   /* 
	    * Assert "ftp" is invalid when
	    * not in allowed schemes 
	    * */ 
	   String[] schemes1 = {"http","https"};
       UrlValidator urlValidator1 = new UrlValidator(schemes1);
       String url = "ftp://your.website.com";
       boolean isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator1.isValid(url)); 
       
       	/* 
	    * Assert "ftp" is valid when
	    * in allowed schemes 
	    * */ 
	   String[] schemes2 = {"http","https", "ftp"};
       UrlValidator urlValidator2 = new UrlValidator(schemes2);
       url = "ftp://www.google.com";
       isValid = true;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator2.isValid(url));
       
       
       /* 
	    * Assert "http" is valid when
	    * in allowed schemes 
	    * */ 
       url = "http://www.google.com";
       isValid = true;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator2.isValid(url));
       
       /* 
	    * Assert "3ht" is invalid scheme
	    * */ 
       url = "3ht://www.google.com";
       isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator2.isValid(url));
       
   }
  
   public void testYourThirdPartition(){
	   /* 
	    * Assert "aaa" is invalid authority 
	    * */ 
       UrlValidator urlValidator = new UrlValidator();
       String url = "http://aaa";
       boolean isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url)); 
       
       /* 
	    * Assert "stackoverflow.com" is valid authority 
	    * */ 
       url = "https://stackoverflow.com";
       isValid = true;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
       
       /* 
	    * Assert "256.256.256.256" is invalid authority
	    * */ 
       url = "http://256.256.256.256";
       isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
       
   } 

   public void testYourForthPartition(){
	   /* 
	    * Assert ":0" is a valid port 
	    * */ 
       UrlValidator urlValidator = new UrlValidator();
       String url = "http://www.google.com:0";
       boolean isValid = true;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
       
       /* 
	    * Assert ":-1" is an invalid port
	    * */ 
       url = "http://www.google.com:-1";
       isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
       
       /* 
	    * Assert ":a" is an invalid port
	    * */ 
       url = "http://www.google.com:a";
       isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
       
   }
   
   public void testYourFifthPartition(){
	   /* 
	    * Assert "/file" is a valid path 
	    * */ 
       UrlValidator urlValidator = new UrlValidator();
       String url = "http://www.google.com/file";
       boolean isValid = true;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
       
       /* 
	    * Assert "/../" is an invalid path
	    * */ 
       url = "http://www.google.com/../";
       isValid = false;
       System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
       
   }
   
 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
