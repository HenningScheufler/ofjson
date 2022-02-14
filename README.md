# ofjson

enables embedding json files in OpenFOAM dictionaries by

```
#json "<case>/test.json";
```

cat test.json:

```json
{
    "string": "string",
    "istream": "istream;",
    "label": 10,
    "scalar": 10.1,
    "vector": [1.1, 2.2, 3.3],
    "subDict": {
        "sub_string": "string",
        "sub_istream": "istream;",
        "sub_label": 10,
        "sub_scalar": 10.1
    },
    "scalarField": {
        "type": "scalarField",
        "value": [1.1, 2.2, 3.3, 4.4]
    }
}
```

The standard OpenFOAM access patterns apply:


```
{
    $string; // would return string
    $scalar; // would return 10
}
```