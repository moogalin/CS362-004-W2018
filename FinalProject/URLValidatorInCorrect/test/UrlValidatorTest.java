

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
		 * http://www.google.com is valid
		 */
		String[] schemes = { "http", "https" };
		UrlValidator urlValidator = new UrlValidator(schemes);
		String url = "http://www.google.com";
		boolean isValid = true;
		assertEquals(url, isValid, urlValidator.isValid(url));
	}

	public void testManualTest2() {
		/*
		 * Assert 
		 * https://www.google.com is valid
		 */
		String[] schemes = { "http", "https" };
		UrlValidator urlValidator = new UrlValidator(schemes);
		String url = "https://www.google.com";
		boolean isValid = true;
		assertEquals(url, isValid, urlValidator.isValid(url));
	}

	public void testManualTest3() {
		/*
		 * Assert
		 * https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%
		 * 2frc%2fdesktops%2f102 is valid
		 */
		String[] schemes = { "http", "https" };
		UrlValidator urlValidator = new UrlValidator(schemes);
		String url = "https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%2frc%2fdesktops%2f102";
		boolean isValid = true;
		assertEquals(url, isValid, urlValidator.isValid(url));
	}

	public void testManualTest4() {
		/*
		 * Assert
		 * https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%
		 * 2frc%2fdesktops%2f102 is valid
		 */
		String[] schemes = { "http", "https" };
		UrlValidator urlValidator = new UrlValidator(schemes);
		String url = "https://www.yahoo.com/?err=404&err_url=https%3a%2f%2fwww.yahoo.com%2ftech%2frc%2fdesktops%2f102";
		boolean isValid = true;
		assertEquals(url, isValid, urlValidator.isValid(url));
	}
	
	public void testManualTest5() {
		/*
		 * Assert
		 * https://www.yahoo.com:80 is valid
		 */
		String[] schemes = { "http", "https" };
		UrlValidator urlValidator = new UrlValidator(schemes);
		String url = "https://www.yahoo.com:80";
		boolean isValid = true;
		assertEquals(url, isValid, urlValidator.isValid(url));
	}

	public void testManualTest6() {
		/*
		 * Assert 
		 * ht://www.google.com is invalid
		 */
		String[] schemes = { "http", "https" };
		UrlValidator urlValidator = new UrlValidator(schemes);
		String url = "ht://www.google.com";
		boolean isValid = false;
		assertEquals(url, isValid, urlValidator.isValid(url));
	}

	public void testManualTest7() {
		/*
		 * Assert 
		 * (blank) is invalid
		 */
		String[] schemes = { "http", "https" };
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
       assertEquals(url, isValid, urlValidator.isValid(url));
       
   }

	   
   public void testYourSecondPartition(){
	   /* 
	    * Assert "ftp" is invalid when
	    * not in allowed schemes 
	    * */ 
	   boolean correct = true;
	   String[] schemes1 = {"http","https"};
       UrlValidator urlValidator1 = new UrlValidator(schemes1);
       String url = "ftp://your.website.com";
       boolean isValid = false;
       if(urlValidator1.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator1.isValid(url)); 
    	   correct = false;
       }       
       /* 
	    * Assert "ftp" is valid when
	    * in allowed schemes 
	    * */ 
	   String[] schemes2 = {"http","https", "ftp"};
       UrlValidator urlValidator2 = new UrlValidator(schemes2);
       url = "ftp://www.google.com";
       isValid = true;
       if(!urlValidator2.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator2.isValid(url));
    	   correct = false;
       }    
       /* 
	    * Assert "http" is valid when
	    * in allowed schemes 
	    * */ 
       url = "http://www.google.com";
       isValid = true;
       if(!urlValidator2.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator2.isValid(url));
    	   correct = false;
       }
       /* 
	    * Assert "3ht" is invalid scheme
	    * */ 
       url = "3ht://www.google.com";
       isValid = false;
       if(urlValidator2.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator2.isValid(url));
    	   correct = false;
       }
       /* 
	    * Assert "https" is valid
	    * */ 
       UrlValidator urlValidator3 = new UrlValidator();
       url = "https://go.com";
       isValid = true;
       if(!urlValidator3.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator3.isValid(url)); 
    	   correct = false;
       }
       /*
        * Assert schemes have passed
        */
       assert(correct);
   }


   public void testYourThirdPartition(){
	   /* 
	    * Assert "aaa" is invalid authority 
	    * */ 
	   boolean correct = true;
	   UrlValidator urlValidator = new UrlValidator();
       String url = "http://aaa";
       boolean isValid = false;
       if(urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url)); 
    	   correct = false;
       }
       /* 
	    * Assert "stackoverflow.com" is valid authority 
	    * */ 
       url = "https://stackoverflow.com";
       isValid = true;
       if(!urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
    	   correct = false;
       }
       /* 
	    * Assert "256.256.256.256" is invalid authority
	    * */ 
       url = "http://256.256.256.256";
       isValid = false;
       if(urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
    	   correct = false;
       }
       /*
        * Assert authorities passed
        */
       assert(correct);
   } 

   public void testYourFourthPartition(){
	   /* 
	    * Assert ":0" is a valid port 
	    * */ 
       boolean correct = true;
	   UrlValidator urlValidator = new UrlValidator();
       String url = "http://www.google.com:0";
       boolean isValid = true;
       if(!urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
    	   correct = false;
       }
       /* 
	    * Assert ":-1" is an invalid port
	    * */ 
       url = "http://www.google.com:-1";
       isValid = false;
       if(urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
    	   correct = false;
       }
       /* 
	    * Assert ":a" is an invalid port
	    * */ 
       url = "http://www.google.com:a";
       isValid = false;
       if(urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
    	   correct = false;
       }
       /*
        * Assert ports have passed
        */
       assert(correct);
   }
   
   public void testYourFifthPartition(){
	   /* 
	    * Assert "/file" is a valid path 
	    * */ 
       boolean correct = true;
	   UrlValidator urlValidator = new UrlValidator();
       String url = "http://www.google.com/file";
       boolean isValid = true;
       if(!urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
    	   correct = false;
       }
       /* 
	    * Assert "/../" is an invalid path
	    * */ 
       url = "http://www.google.com/../";
       isValid = false;
       if(urlValidator.isValid(url)) {
    	   System.out.println(url + " expected " + isValid + ", returned " + urlValidator.isValid(url));
    	   correct = false;
       }
       /*
        * Assert paths have passed
        */
       assert(correct);
   }
   
 
   
   public void testIsValid()
   {
	   int numTests = 25;
	   int failedTestCount = 0;
	   System.out.println("\nSTARTING: testIsValid");
	   
	   /* Odd indexed Strings in array are incorrect. */
	   String[] schemes = new String[]{ "http://", "3ht://", "ftp://", "http:/", "h3t://", "http:", "" };
	   String[] authority = new String[]{"www.google.com", "256.256.256.256", "go.com", "1.2.3.4.5", "go.au", ""};
	   String[] port = new String[]{":80", ":-1", ":65535", ":65636", ":0", ":65a"};
	   /*First five are paths and last five are pathoptions*/
	   String[] pathAndPathOptions = new String[]{"/test1", "/..", "/t123", "/../", "/test1/file", "/..//file", "", "/#", "/$23/file", "/#/file", "/test1//file"};
	   
	   UrlValidator urlValidator = new UrlValidator(schemes);
	   
	   for (int i = 0; i <= numTests; i++) {
		   Random ran = new Random();
		   int schemeIndex = ran.nextInt(schemes.length);
		   ran = new Random();
		   int authorityIndex = ran.nextInt(authority.length);
		   ran = new Random();
		   int portIndex = ran.nextInt(port.length);
		   ran = new Random();
		   int pathAndPathOptionsIndex = ran.nextInt(pathAndPathOptions.length);
		   
		   boolean isValid = true;	   
		   if(schemeIndex % 2 == 1 || authorityIndex % 2 == 1 || portIndex % 2 == 1 || pathAndPathOptionsIndex % 2 == 1) {
			    isValid = false;
			    failedTestCount++;
			    
		   }
		   
		   String url = schemes[schemeIndex] + authority[authorityIndex] + port[portIndex] + pathAndPathOptions[pathAndPathOptionsIndex];
		   Boolean result = urlValidator.isValid(url);
		   if(result == isValid) {
			   System.out.println("SUCCESS: " + url + " is " + isValid);
		   } else {
			   System.out.println("ERROR: " + url + " is supposed to be " + isValid);
		   }
	   }
	   System.out.println("COMPLETED: testIsValid\n");
	   assertEquals(0, failedTestCount);
   }
   


}
