/* author: Parveen Sabah
 * Cite: Professor's Lecture and pseudo code
 * StackOverflow
 * My friend Vamsi helped me
 * */
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;


class HashMapLC {
	class DoubleLinkedList {
		DoubleLinkedList next, prev;
		DoubleLinkedList temp;
		String key;
		int value;

		public DoubleLinkedList(String key, int value) {
			this.key = key;
			this.value = value;
			next = null;
			prev = null;
		}

		public String getKey() {
			return key;
		}

		public int getValue() {
			return value;
		}

		public DoubleLinkedList getTemp() {
			return temp;
		}

	}
	DoubleLinkedList[] table;
	int size;

	public HashMapLC(int tableSize) {
		table = new DoubleLinkedList[tableSize];
		size = tableSize;
	}

	/*public void grow() {
		capacity *= 2;
		DoubleLinkedList temp = new DoubleLinkedList[tableSize];
		tableSize = new DoubleLinkedList[capacity];
		this.size = 0;
		for(int i=0; i<capacity; i++)
			tableSize.add(null);
		for(DoubleLinkedList list : temp) {
			if(list == null) {
			}
			else {
				for(String word : list)
					add(word);
			}
		}
	}*/

	private int hash(String key) {
		int hashValue = key.hashCode();
		hashValue %= table.length;
		if(hashValue < 0)
			hashValue += table.length;

		return hashValue;		
	}

	public void add(String key, int value) {
		int pos = hash(key);
		DoubleLinkedList node = new DoubleLinkedList(key, value);
		DoubleLinkedList start = table[pos];

		if(table[pos] == null)
			table[pos] = node;
		else {
			node.next = start;
			start.prev = node;
			table[pos] = node;
		}
	}

	public int get(String key) {
		int pos = hash(key);
		if(table[pos] == null)
			return -1;
		else {
			DoubleLinkedList entry = table[pos];
			while(entry != null && entry.getKey() == key) {
				entry = entry.getTemp();
			}
			if(entry == null)
				return -1;
			else {
				if(entry.getKey().hashCode() == key.hashCode()) {
					return entry.getValue();
				}
				else {
					return -1;
				}
			}
		}
	}

	private int findSize(DoubleLinkedList temp) {
		int i=0;
		while(temp != null) {
			i++;
			temp = temp.next;
		}
		return i;
	}

	public void hist() {
		int hist[] = new int[10];
		int temp = 0;
		System.out.println();
		for(int i=0; i<table.length; i++) {
			if(table[i] == null) {
				hist[0]++;
			}
			else {
				DoubleLinkedList start = table[i];
				if(start != null) {
					temp = findSize(start);
				}
				if(temp == 1)
					hist[1]++;
				if(temp == 2)
					hist[2]++;
				if(temp == 3)
					hist[3]++;
				if(temp == 4)
					hist[4]++;
				if(temp == 5)
					hist[5]++;
				if(temp == 6)
					hist[6]++;
				if(temp == 7)
					hist[7]++;
				if(temp == 8)
					hist[8]++;
				if(temp == 9)
					hist[9]++;
			}
		}
		for(int i=0; i<10; i++)
			System.out.println("Bins with "+i+ " elements : " + hist[i]);
	}

	public static void main(String[] args) {
		int n = 1000000;
		HashMapLC arb = new HashMapLC(n);
		int count =0;
		List<String> dict = new ArrayList<String>();
		BufferedReader br = null;

		try {
			File file = new File("dict.txt");
			FileReader fr = new FileReader(file);
			br = new BufferedReader(fr);
			String line = br.readLine();
			while(line != null) {
				String word = line.trim();
				dict.add(word);
				line = br.readLine();
			}
		}catch(IOException e) {
			e.printStackTrace();
		}finally {
			try {
				if(br != null)
					br.close();
			} catch(IOException e) {
				e.printStackTrace();
			}
		}
		String[] dict_array = dict.toArray(new String[0]);
		System.out.println(dict_array.length);
		for(int i=0; i<dict_array.length; i++) {
			arb.add(dict_array[i], count);
			count++;
		}


		final String words[] = {"apple", "bear", "cat", "dog", "arggg",
		"juwqehtrkqwejhr", "underbishop", "ting", "wonderwall"};

		System.out.println("\n\nLinear Chaining");
		for(int i=0; i<words.length; i++) {
			Integer id = arb.get(words[i]);
			System.out.println("Word: '" + words[i] +
					"' stored at the index: " + id);
		}
		arb.hist();
	}
}


