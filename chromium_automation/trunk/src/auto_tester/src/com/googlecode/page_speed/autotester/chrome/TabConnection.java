// Copyright 2011 Google Inc. All Rights Reserved.

package com.googlecode.page_speed.autotester.chrome;

import org.json.simple.JSONObject;

/**
 * Represents an open debugging connection to a Chrome tab, using the protocol described at
 * <code>http://code.google.com/chrome/devtools/docs/remote-debugging.html</code>.  A concrete
 * implementation is provided by <code>ChromeTab.connect(int)</code>, or this class can be mocked
 * out for testing.
 *
 * The Chrome remote debugging API has basically two forms of communication.  The first form is
 * remote method calls: the caller sends a message containing a UID, a method name, and a
 * dictionary of parameters, and Chrome responds with a dictionary of results or an error message.
 * This form is handled primarily by the <code>asyncCall</code> method, which automatically deals
 * with assigning UIDs behind the scenes and routing asynchronous responses back to the correct
 * callback object.
 *
 * The second form consists of intermittent notication messages, categories of which can be enabled
 * or disabled by appropriate remote method calls.  This form is handled by the
 * <code>setNotificationListener</code> method, which sets an object to receive all of these
 * notifications and handle them appropriately.
 *
 * @author mdsteele@google.com (Matthew D. Steele)
 */
public abstract class TabConnection {

  /**
   * Set a listener to be called each time a notification message arrives from the Chrome tab.
   * Call this method with null to remove any currently active listener.
   */
  public abstract void setNotificationListener(NotificationListener listener);

  /**
   * This is a convenience method for calling <code>asyncCall</code> with an empty parameters
   * object.
   */
  public void asyncCall(String methodName, AsyncCallback callback) {
    this.asyncCall(methodName, new JSONObject(), callback);
  }

  /**
   * Make an asynchronous remote method call to the Chrome tab.  If any error occurs (either one
   * reported by Chomre, or else an I/O error) it will be reported to
   * <code>AsyncCallback.onError</code>.
   */
  public abstract void asyncCall(String methodName, JSONObject params, AsyncCallback callback);

  /**
   * Determine if there are remote calls that have been made to the Chrome tab that have not yet
   * returned.
   *
   * @return true if there are still any outstanding calls (and the connection is still open).
   */
  public abstract boolean hasOutstandingCalls();

  /**
   * Close the connection to the Chrome tab.  No more notifications will be received and all
   * outstanding calls will be cancelled with an error.
   */
  public abstract void close();

  /**
   * This is a convenience method for calling <code>syncCall</code> with an empty parameters
   * object.
   */
  public JSONObject syncCall(String methodName) throws CallFailureException {
    return this.syncCall(methodName, new JSONObject());
  }

  /**
   * Make a synchronous call to the Chrome tab.  This is like <code>asyncCall</code>, but blocks
   * until the method returns.
   *
   * @returns the result of the call to Chrome (if the call succeeds).
   * @throws CallFailureException if there is a problem connecting to Chrome, if Chrome reports
   *   an error, or if the thread is interrupted while waiting for the response.
   */
  public JSONObject syncCall(String methodName, JSONObject params) throws CallFailureException {
    SyncCaller caller = new SyncCaller();
    this.asyncCall(methodName, params, caller.getCallback());
    return caller.waitForCallback();
  }

  /**
   * A private helper class for <code>syncCall</code>.
   */
  private static class SyncCaller {

    JSONObject result = null;
    String error = null;

    public AsyncCallback getCallback() {
      return new AsyncCallback() {
        public void onSuccess(JSONObject result) {
          synchronized (SyncCaller.this) {
            SyncCaller.this.result = result;
            SyncCaller.this.notifyAll();
          }
        }
        public void onError(String error) {
          synchronized (SyncCaller.this) {
            SyncCaller.this.error = error;
            SyncCaller.this.notifyAll();
          }
        }
      };
    }

    public synchronized JSONObject waitForCallback() throws CallFailureException {
      while (this.result == null && this.error == null) {
        try {
          this.wait();
        } catch (InterruptedException e) {
          throw new CallFailureException("interrupted");
        }
      }

      if (this.error != null) {
        throw new CallFailureException(this.error);
      }

      return this.result;
    }
  }

}
