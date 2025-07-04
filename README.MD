Example usage:

```c
#include <stdio.h>
#include "webhook.c"

int main() {
  Webhook example;
  example.url = "https://discord.com/api/webhooks/xxxxxxxxxxxxxx/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  example.name = "test";

  webhook_message_send(example, "polymorqhism is so goated");
  webhook_edit(&example, "poly");
  webhook_delete(example);

}
```
