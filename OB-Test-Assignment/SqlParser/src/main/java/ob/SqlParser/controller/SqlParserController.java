package ob.SqlParser.controller;

import ob.SqlParser.service.SqlParserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class SqlParserController {

    private SqlParserService sqlparserService;

    @Autowired
    public SqlParserController(SqlParserService sqlparserService) {
        this.sqlparserService = sqlparserService;
    }

    @PostMapping(value = "/api/query", consumes = "text/plain")
    public String ParseQuery(@RequestBody String query) {
        return sqlparserService.parseQuery(query);
    }
}
