

public class StringChopping {
    public static int ceiling(double x) {
        return (int) Math.ceil(x);
    }


    /**
     * Chop the specified segment of the given string <code>s</code>
     *
     * @param s       the string to chop
     * @param segment the segment of s to chop, and is one of: 'h' or 'H' for head, 'm' or 'M' for middle, 't' or 'T' for tail
     * @return the string after removing the specified segment from s
     */
    public static String chopString(String s, char segment) {
        int string_length = s.length();

        if (segment == 'h' || segment == 'H') {
            int head_length = ceiling((double)string_length / 3);
            s = s.substring(head_length, string_length);
        } else if (segment == 'm' || segment == 'M') {
            int head_length = ceiling((double)string_length / 3);
            int middle_length = string_length - 2 * ceiling((double)string_length / 3);
            s = s.substring(0, head_length + 1) + s.substring(string_length - head_length, string_length);

        } else if (segment == 't' || segment == 'T') {
            int tail_length = ceiling((double)string_length / 3);
            s = s.substring(0, string_length - tail_length);

        } else {
            System.out.println("character is non valid");
        }

        return s;
    }

    /**
     * Determine a chop sequence that will result in the provided string being
     * cut down to the target character
     *
     * @param s      the string to dice
     * @param target the last character that should remain after a sequence of chop operations
     * @return a string that represents the sequence of chop operations needed to obtain exactly <code>target</code> and "NO" if no such sequence exists
     */
    public static String diceStringTo(String s, char target) {
        int string_length = s.length();
        int target_index = -1;

        for (int i = string_length - 1; i >= 0; i--) {
            if (s.charAt(i) == target) {
                target_index = i;
                break;
            }

        }
        if (target_index == -1) return "NO";


        String sequence = "";
        while (string_length > 1) {
            target_index = s.indexOf(target);
            if(target_index == -1){
                System.out.println("letter not in substring");
                return "NO";
            }
            else if (target_index > ceiling((double) string_length / 3)) {
                s = chopString(s, 'H');
                sequence += "H";
            } else {
                s = chopString(s, 'T');
                sequence += "T";
            }

            string_length = s.length();
        }


        return sequence;
    }

    /**
     * Obtain an array that contains all dice sequences for the given string,
     * with the first element of the array representing 'a' as the target
     * and the last element of the array representing 'z' as the target
     *
     * @param s the string to dice
     * @return an array of dicing sequences for <code>s</code>
     * with targets from 'a' to 'z', in that order
     */
    public static String[] allPossibleDicings(String s) {
        char[] letters = new char[26];  // 26 letters in the alphabet

        for (int i = 0; i < 26; i++) {
            letters[i] = (char) ('a' + i);
        }

        String[] sequences = new String[26];

        for (int i = 0; i < 26; i++) {
            sequences[i] = diceStringTo(s, letters[i]);
            System.out.println(sequences[i] + "  " + letters[i]);
        }
        return sequences;
    }
}