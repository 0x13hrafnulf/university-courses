package ob.First.model;

import com.fasterxml.jackson.annotation.JsonValue;

public enum ClientStatus {
    ACTIVE("active"),
    INACTIVE("inactive");

    ClientStatus(String status)
    {
        this.status = status;
    }

    private String status;
    @JsonValue
    public String getStatus() {
        return status;
    }
}
