package ob.SqlParser.service;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
@Service
public class SqlParserService {

    public String parseQuery(String query) {
        List<String> columns = new ArrayList<>();
        String pre_query = query.replace("\n", " ").replace("\r", " ");
        List<String> processed_query = processQuery(pre_query);
        String result = String.join(",", processed_query);

        return result;
    }

    private List<String> processQuery(String query) {
        List<String> tokens = new ArrayList<>();
        String[] query_split = query.split(" ", 2);
        HashMap<String, String> subqueries = parseSubqueries(query_split[1]);

        int index_from = query_split[1].lastIndexOf("from");
        String columns_string = query_split[1].substring(0, index_from);
        String[] columns = columns_string.split(",");

        for(String token : columns) {
            String[] tmp_split = token.split(" ");
            String tmp = tmp_split[tmp_split.length - 1];
            tokens.add(tmp.substring(tmp.indexOf(".") + 1));
        }

        //HashMap<String, String> columns_map = parseColumns(columns_string);

        return tokens;
    }

    private HashMap<String, String> parseSubqueries(String query_portion) {
        String query_copy = query_portion;
        HashMap<String, String> subqueries = new HashMap<>();

        int subq_start = query_copy.indexOf("(");
        int subq_end = query_copy.indexOf(")");
        int track = 1;
        while(subq_start != -1 && subq_end != -1)
        {
            String key = String.join("", "subquery", Integer.toString(track));
            String subq = query_copy.substring(subq_start, subq_end + 1);
            subqueries.put(key, subq);
            query_copy = query_copy.replace(subq, key);
            track += 1;
            subq_start = query_copy.indexOf("(");
            subq_end = query_copy.indexOf(")");
        }
        return subqueries;
    }

    private HashMap<String, String> parseColumns(String column_portion) {
        HashMap<String, String> result = new HashMap<>();

        String[] columns = column_portion.split(",");

        for(String column : columns) {
            String[] tmp_split = column.trim().split(" ");
            String tmp = tmp_split[tmp_split.length - 1];
            result.put(tmp_split[0], tmp.substring(tmp.indexOf(".") + 1));
        }

        result.entrySet().forEach(entry -> {
            System.out.println(entry.getKey() + " " + entry.getValue());
        });

        return result;
    }
}
