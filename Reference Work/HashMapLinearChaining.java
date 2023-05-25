/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.yihang.datastructure;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author yihangyuan
 */
public class HashMapLinearChaining {

    private ArrayList<LinkedList<String>> table;
    
    int lineNum;// txt file word number
    int capacity; // table size
    public int size; // how many values are in the table, check for grow()
    public BufferedReader br;

    public HashMapLinearChaining(BufferedReader br) {

        this.br = br;
        this.lineNum = getNumLine(br);
        this.capacity = (int) (lineNum * 1.5);

        table = new ArrayList<LinkedList<String>>(capacity);
        for (int i = 0; i < capacity; i++) { //filled with null
            table.add(null);
        }

    }

    public void grow() { // grow table, rehash
        capacity *= 2;
        ArrayList<LinkedList<String>> temp = new ArrayList<LinkedList<String>>(table);
        table = new ArrayList<LinkedList<String>>(capacity);
        this.size = 0; //reset size to 0

        for (int i = 0; i < capacity; i++) { //filled with null
            table.add(null);
        }

        for (LinkedList<String> list : temp) {//rehash
            if (list == null) {

            } else {
                for (String word : list) {
                    add(word);
                }
            }
        }

    }

    public void add(String key) { // add a word into HashMap
        int hashvalue = hashFunction(key);
        LinkedList<String> list;

        if (table.get(hashvalue) == null) {
            this.size += 1; // if this bin occupied, size +=1
            list = new LinkedList<String>();
        } else {
            list = table.get(hashvalue);
        }
        list.add(key);
        table.set(hashvalue, list);

    }

    public boolean get(String key) { // check if word in HashMap or not

        int hashvalue = hashFunction(key);
        if (table.get(hashvalue) != null) {
            // TODO: implement this

            LinkedList<String> list = table.get(hashvalue);
            for (String word : list) {
                if (word.equals(key)) {
                    return true;
                }

            }
        }
        return false;
    }

    // remove an key-value pair from the hash map
    public void remove(String key) {
        LinkedList<String> list;
        int hashvalue = hashFunction(key);
        if (get(key) != false) {
            list = table.get(hashvalue);
            list.remove(key);
            table.set(hashvalue, list);
        }

    }

    public void histogram() {

        int[] count = new int[10];

        for (LinkedList<String> list : table) {
            if (list == null) {
                count[0] += 1;
            } else {
                int number = 0;
                for (String word : list) {
                    number += 1;
                }
                if (number > 9) {
                    count[9] += 1;
                } else {
                    count[number] += 1;
                }

            }

        }

        for (int i = 0; i < 10; i++) {
            System.out.println("insert" + i + "    " + "count" + count[i]);
        }
        double average = (double)lineNum / (double)size;
        System.out.println("average bin size is " + average);

    }

    public int hashFunction(String str) {

        long value = 1;
        for (int index = 0; index < str.length(); index++) {
            value = value * 3 + (int) str.charAt(index);
        }

        return (int) (value % capacity);
    }

    public static int getNumLine(BufferedReader br) { // how many word are in the .txt file

        String st;
        int count = 0;
        try {
            while ((st = br.readLine()) != null) {
                count++;
            }
        } catch (IOException ex) {
            Logger.getLogger(HashMapLinearChaining.class.getName()).log(Level.SEVERE, null, ex);
        }

        return count;
    }

    public static void main(String[] args) throws Exception {

        String st;
        File a = new File("dict.txt"); // this is the dictionary file  
        BufferedReader br = new BufferedReader(new FileReader(a));

        HashMapLinearChaining HashMap = new HashMapLinearChaining(br);

        BufferedReader br2 = new BufferedReader(new FileReader(a));// because .readline() is exausted for getLineNum(), so I reload file for add word

        while ((st = br2.readLine()) != null) { // add dict.txt into the Trie

            if (HashMap.size / HashMap.capacity >= 0.75) {
                
                HashMap.grow(); // grow() if table is about 75% full
            }
            
            HashMap.add(st);
        }

        HashMap.histogram();
        
        
        // following code is for read .dat file. Check if each word in HashMap
        // uncomment following to use it
        // NOTICE:I don't have .dat file to test it, so this code may have bugs!
        
//        File file = new File("spell.dat");
//        Scanner scnr = new Scanner(file);
//        while (scnr.hasNextLine()) {
//            String line = scnr.nextLine();
//            if(HashMap.get(line) == true){
//                System.out.println(line + " is not in this HashMap");
//            }
//            else{
//                System.out.println(line + " is in this HashMap");
//            }
//            
//        }

    }
}
