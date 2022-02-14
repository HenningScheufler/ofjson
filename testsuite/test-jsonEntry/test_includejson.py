import os
import oftest
from oftest import run_reset_case
import json

def test_includejson(run_reset_case):

    assert (run_reset_case.success)
